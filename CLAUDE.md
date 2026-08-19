# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Projet

cub3D — moteur de raycasting (style Wolfenstein 3D) en C, cursus 42 (rendu 2023). Rendu "fausse 3D" via DDA, MiniLibX/X11. Bonus = armes, sprites/cibles, portes, souris, minimap, sol/plafond texturés.

La branche `main` conserve le rendu 2023 d'origine, tel quel. `modernize-2026` porte la version modernisée décrite ici — les deux divergent volontairement.

## Build & run

```bash
cd mlx && ./configure && cd ..   # bâtit libmlx.a (l'erreur finale sur test/ est sans effet)
make          # -> ./cub3D        (mandatory)
make bonus    # -> ./cub3D_bonus  (bonus)
./cub3D maps/test_mandatory.cub
./cub3D_bonus maps/shooting_range.cub
```

- **Arbre unique** : `src/` compile les deux binaires. Le bonus, c'est `-D BONUS` — les écarts sont des blocs `#ifdef BONUS` dans les fichiers partagés, plus les fichiers listés dans `BONUS_SRC` (arme, sprites, souris, sol/plafond texturés).
- Objets séparés (`obj/std/`, `obj/bonus/`) : mêmes sources, flags différents. Pas de `make re` en switchant.
- Deps : `mlx/` (vendorisée, patchée `-std=gnu17 -fcommon` pour compiler sous C23) et `utils/get_next_line/`. libft a été supprimée — le stdlib réel est utilisé ; les 3 helpers sans équivalent (`ft_split`, `ft_strtrim`, `ft_strjoin`) sont dans `src/utils/str.c`. Attention : `ft_strjoin` **libère `s1`**.
- `CFLAGS` : `-O3 -march=native -flto -ffast-math -pthread`. Les deux `-Wno-*` couvrent l'API callback legacy de MiniLibX et les `system()` audio volontairement fire-and-forget.
- Pas de framework de test. La norminette ne s'applique plus (threads, `static inline`, >5 variables assumés).
- `maps/shooting_range.cub` utilise les chars bonus `D`/`T` : le binaire mandatory la **rejette**, c'est normal. Utiliser `maps/test_mandatory.cub`.

## Architecture

Un seul mega-struct `t_cub` (include/main.h) passé partout par pointeur, agrégeant des sous-structs par domaine (`t_ray`, `t_engine`, `t_texture`…). Tout l'état vit là — pas de globales.

Flux : `main` → `master_parser` (parse .cub) → `ft_init_direction` → `ft_cub` (init MiniLibX, hooks, `mlx_loop`) → `ft_render` à chaque frame (loop hook).

- `src/parse/` — lecture .cub via get_next_line. Ordre imposé : configs (NO/SO/EA/WE, F/C) **avant** la map ; toute config après = erreur. `check_map` valide la fermeture.
- `src/main/` — rendu. `render.c` : `cast_ray` découpe les colonnes en bandes sur N threads. `draw3D.c` : `draw_texture` échantillonne le mur. `z_buffer` (taille WIDTH) pour l'occlusion des sprites.
- `src/moves/` — entrées clavier bufferisées dans `t_keys`, appliquées chaque frame dans `ft_move`/`ft_rotate` (mouvement fluide, pas événementiel).

### Ce qu'il ne faut pas casser

- **Threads** : chaque thread reçoit une **copie de `t_cub`**, donc le scratch par-colonne (`t_ray`, `t_ceiling`, `t_floor`) est thread-local. La caméra (`dir/plane/player`) est en lecture seule pendant le cast, et les écritures pixels/z_buffer visent des index disjoints. Écrire dans le `t_cub` partagé depuis `render3d` ou plus bas casserait ça.
- **Adresses de texture** : `mlx_get_data_addr` est appelé **une fois par colonne**, jamais par pixel — c'est là qu'était le gros du coût.
- **Boucle de rendu sans malloc** : le HUD utilise `snprintf` sur buffer pile. Ne pas y réintroduire d'allocation.

## Conventions

- Constantes (WIDTH/HEIGHT, vitesses, chemins textures/audio, keycodes) = `#define` dans include/main.h.
- Textures/sprites = `.xpm` (`sprite/`), audio `.wav` (`audio/`, joué via `system("aplay ... &")`, coupé par `pkill aplay`).
- Erreurs : `ft_error` / `ft_error_free` / `ft_error_parse` (message + free + exit). Nettoyage via `ft_free_map`, `free_texture`, `free_door`.
