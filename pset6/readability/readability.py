import cs50

letters = 0
words = 0
sentences = 0

def main():
    # prompt user for input
    text = cs50.get_string("Text: ")

    # count letters, words, sentences
    for i in range(len(text)):
        count_letters(text[i])
        count_words(text[i])
        count_sentences(text[i])

    # calculate average letters and sentences
    L = (letters * 100) / (words + 1)
    S = (sentences * 100) / (words + 1)

    # calculate coleman-liau index
    index = round((0.0588 * L) - (0.296 * S) - 15.8)

    # print grade level of text
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")

# count letters
def count_letters(x):
    global letters
    if x.isalpha():
        letters += 1

# count words
def count_words(x):
    global words
    if x == ' ':
        words += 1

# count sentences
def count_sentences(x):
    global sentences
    if x == '.' or x == '!' or x == '?':
        sentences += 1

main()