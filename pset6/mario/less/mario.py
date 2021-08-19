import cs50

# prompt user for height
while True:
    n = cs50.get_int("Height: ")
    if n >= 1 and n <= 8:
        break

# print lines
for lines in range(1, n + 1):
    # print spaces
    for spaces in range(1, n - lines + 1):
        print(" ", end="")
    # print hashes
    for hashes in range(1, lines + 1):
        print("#", end="")
    # print new line
    print("")