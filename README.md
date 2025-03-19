# Cub3D

Cub3D is a 3D game project inspired by Wolfenstein 3D, developed as part of the 42 School curriculum. It uses raycasting to render a simple 3D environment based on a 2D map.

## Features
- Raycasting engine for 3D rendering
- Player movement and rotation
- Wall collision detection
- Textured walls and floor/ceiling coloring
- Mini-map display (optional)

## Installation
### Prerequisites
Ensure you have the following dependencies installed:
- A Unix-based system (Linux or macOS)
- `make` and `gcc`
- `mlx` (MinilibX graphics library)

### Clone the repository
```sh
git clone https://github.com/bou1337/cub3d.git
cd cub3d
```

### Build the project
```sh
make
```

## Usage
Run the game with:
```sh
./cub3D maps/example.cub
```

### Controls
- `WASD` - Move forward, backward, and strafe left/right
- `Left/Right Arrow` - Rotate view
- `ESC` - Exit the game

## Map File Format
The game uses `.cub` files to define the environment. The file includes:
- Resolution settings
- Texture file paths for walls
- Floor and ceiling colors
- Map layout with `1` for walls and `0` for empty space

Example:
```
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm
F 220,100,0
C 225,225,225
111111
100001
100001
111111
```

## Acknowledgments
This project is part of the 42 curriculum and follows the specified requirements.

## License
This project is for educational purposes and follows 42's academic policies.

---

Feel free to contribute or reach out if you have any questions!

