d = {}
unique_letter_count, code_length = map(int,input().split())
for _ in range(unique_letter_count):
  parse_me = input();
  letter = parse_me[0]
  code = parse_me[3:]
  d[code] = letter

coded_string = input()
pointer = 0
encoded_string = ""

while (pointer < code_length):
  for i in d:
    if(coded_string.startswith(i,pointer)):
      encoded_string += d[i]
      pointer += len(i)

print(encoded_string)