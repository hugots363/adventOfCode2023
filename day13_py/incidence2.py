def distance(l: str, r: str) -> int:
    return sum(a != b for a, b in zip(l, r))


def reflection_row(block: list[str], distance_to_match: int) -> int:
    for idx in range(1, len(block)):
        if (
            sum(distance(l, r) for l, r in zip(reversed(block[:idx]), block[idx:]))
            == distance_to_match
        ):
            return idx

    return 0


def score_block(block: str, distance_to_match: int) -> int:
    rows = block.split("\n")
    if row := reflection_row(rows, distance_to_match):
        return 100 * row

    if col := reflection_row(list(zip(*rows)), distance_to_match):
        return col

    raise ValueError("no reflection found!")




def main():
    input_file = "input.txt"

    with open(input_file, 'r') as f:
        input_data = f.read()
    print(sum(score_block(block, 1) for block in input_data.split("\n\n")))
 
if __name__ == "__main__":
    main()
