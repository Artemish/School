from bisect import bisect_left

# Discard the carriage returns and newlines in the document
File = open("dict.txt")
dictionary = [line[0:-2] for line in File.readlines()]
File.close()
 
def binary_search(lst, el):
  index = bisect_left(lst, el)
  if (index == len(lst)) or (lst[index] != el):
    return -1
  else:
    return index

def is_english_word(word):
  return (binary_search(dictionary, word) != -1)
