from pathlib import Path

from PIL import Image, ImageDraw


BOARD_SIZE = 8
CELL_SIZE = 100
IMAGE_SIZE = BOARD_SIZE * CELL_SIZE

LIGHT_COLOR = (230, 238, 250)
DARK_COLOR = (72, 97, 140)

OUTPUT_FILE = (
    Path(__file__).resolve().parent
    / "assets"
    / "board"
    / "chess_board.bmp"
)


def main() -> None:
    OUTPUT_FILE.parent.mkdir(
        parents=True,
        exist_ok=True,
    )

    board = Image.new(
        "RGB",
        (IMAGE_SIZE, IMAGE_SIZE),
        LIGHT_COLOR,
    )

    draw = ImageDraw.Draw(board)

    for row in range(BOARD_SIZE):
        for col in range(BOARD_SIZE):
            color = (
                LIGHT_COLOR
                if (row + col) % 2 == 0
                else DARK_COLOR
            )

            left = col * CELL_SIZE
            top = row * CELL_SIZE
            right = left + CELL_SIZE - 1
            bottom = top + CELL_SIZE - 1

            draw.rectangle(
                (left, top, right, bottom),
                fill=color,
            )

    board.save(
        OUTPUT_FILE,
        format="BMP",
    )

    print(f"Created: {OUTPUT_FILE}")
    print(f"File size: {OUTPUT_FILE.stat().st_size} bytes")


if __name__ == "__main__":
    main()