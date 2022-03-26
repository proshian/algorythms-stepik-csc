def fib_mod(n, m):
  period = 3
  fl = [0,1,1]
  counter = 2

  while(1):
    lastel = (fl[-1]+fl[-2])%m
    if lastel == 1 and fl[-1] == 1 and fl[-2] == 0:
      period = counter-1
      break;
    fl.append(lastel)
    counter +=1
  
  return fl[n%period]


def main():
    n, m = map(int, input().split())
    print(fib_mod(n, m))


if __name__ == "__main__":
    main()