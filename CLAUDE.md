# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Projet

cub3D — moteur de raycasting (style Wolfenstein 3D) en C, cursus 42. Rendu "fausse 3D" via DDA, MiniLibX/X11. Bonus = armes, sprites/cibles, portes, souris.

## Build & run

```bash
make          # binaire standard -> ./cub3D
make bonus    # binaire bonus    -> ./cub3D  (MEME nom, ecrase le standard)
make re       # OBLIGATOIRE en switchant standard <-> bonus (binaire partage)
./cub3D maps/shooting_range.cub
```

- Objets dans `obj/` (miroir de l'arbre source). `make clean` supprime `obj/`, `fclean` supprime aussi le binaire.
- Deps vendorisees compilees par le Makefile : `mlx/` (MiniLibX linux), `utils/libft/`, `utils/get_next_line/`. Lien : `-lmlx -lX11 -lXext -lm`.
- Pas de framework de test. Norme 42 (norminette) : 25 lignes/fonction, pas de `for`, structs déclarées en header uniquement.
- README : `maps/map.cub` et `cub3D_bonus` n'existent pas — seule map réelle = `maps/shooting_range.cub`, binaire toujours `cub3D`.

## Architecture

Un seul mega-struct `t_cub` (include/main.h) passé partout par pointeur ; il agrège des sous-structs par domaine (`t_ray`, `t_engine`, `t_texture`, `t_sprite`, `t_img`, etc.). Tout l'état vit là — pas de globales.

Flux (`src/main/main.c`) :
`main` → `master_parser` (parse .cub) → `ft_init_direction` → `ft_cub` (init MiniLibX, hooks, `mlx_loop`) → boucle via `ft_render` (loop hook).

Sous-systèmes (dossiers = domaines) :
- `src/parse/` — lecture .cub via get_next_line. Ordre imposé : configs (NO/SO/EA/WE, F/C couleurs) AVANT la map ; toute config après le début de map = erreur (`process_map_lines`). `check_map` valide que la map est fermée (flood/bordure).
- `src/main/` — rendu. `render.c` : `cast_ray` lance un rayon par colonne mais **rend 2 colonnes à la fois** (`render3d(x)`+`render3d(x+1)`, `x += 2`) pour la perf. `ft_caster` = boucle DDA. `draw3D.c`/`draw.c`/`texture.c` : murs texturés + sol/plafond. `z_buffer` (taille WIDTH) pour l'occlusion des sprites.
- `src/moves/` — entrées clavier bufferisées dans `t_keys` (press/release), appliquées chaque frame dans `ft_move`/`ft_rotate` (mouvement fluide, pas événementiel).

Bonus = superset : mêmes dossiers, fichiers en plus — `draw_weapon.c`, `draw_sprite*.c`, `weapon.c`, `mouse.c`, `draw3D_utils.c`. La logique porte/cible/arme est intégrée au flux de rendu et au parsing (chars `D` porte, `T` cible, `N/S/E/W` spawn joueur).

## Conventions

- Constantes de jeu (WIDTH/HEIGHT, vitesses, chemins textures/audio, keycodes) = `#define` dans include/main.h.
- Textures/sprites = fichiers `.xpm` (`sprite/`), audio `.wav` (`audio/`, joué via `system("aplay ... &")`, coupé par `pkill aplay`).
- Erreurs : `ft_error` / `ft_error_free` / `ft_error_parse` (message + free + exit). Nettoyage via `ft_free_map`, `free_texture`, `free_door`.
