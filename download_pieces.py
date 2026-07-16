from pathlib import Path
from urllib.request import Request, urlopen
from urllib.error import URLError, HTTPError

BASE_URL = (
    "https://cdn.jsdelivr.net/gh/oakmac/chessboardjs@1.0.0/"
    "website/img/chesspieces/wikipedia"
)

PIECES = [
    "wK", "wQ", "wR", "wB", "wN", "wP",
    "bK", "bQ", "bR", "bB", "bN", "bP",
]

OUTPUT_DIR = Path("assets") / "pieces"
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)


def download_piece(piece_name: str) -> None:
    url = f"{BASE_URL}/{piece_name}.png"
    output_path = OUTPUT_DIR / f"{piece_name}.png"

    request = Request(
        url,
        headers={
            "User-Agent": "Mozilla/5.0"
        },
    )

    try:
        with urlopen(request, timeout=30) as response:
            output_path.write_bytes(response.read())

        print(f"Saved: {output_path}")

    except HTTPError as error:
        print(
            f"HTTP error for {piece_name}: "
            f"{error.code} {error.reason}"
        )

    except URLError as error:
        print(
            f"Network error for {piece_name}: "
            f"{error.reason}"
        )

    except OSError as error:
        print(
            f"File error for {piece_name}: "
            f"{error}"
        )


def main() -> None:
    print("Starting download...")

    for piece in PIECES:
        download_piece(piece)

    print("Finished.")


if __name__ == "__main__":
    main()