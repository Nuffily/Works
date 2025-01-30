"""
Функция, выводящая деление столбиком двух натуральных чисел
"""

import sys

def long_division(dividend, divider):
    answer = (str(dividend) + '|' + str(divider)) + "\n"

    if dividend < divider:
        answer += (str(dividend) + '|' + "0") + "\n"
        return

    dividend_used = 0
    cur_dividend = str(dividend)[dividend_used]
    dividend_used += 1
    first_time = True
    shift = 0

    while True:
        cur_divider = 0
        while int(cur_dividend) < divider:
            if dividend_used == len(str(dividend)):
                break
            cur_dividend += str(dividend)[dividend_used]
            dividend_used += 1

        while len(cur_dividend) > 1 and cur_dividend[0] == "0":
            cur_dividend = cur_dividend[1:]
            shift += 1

        if not first_time:
            answer += (shift * " " + cur_dividend) + "\n"

        while True:
            if cur_divider + divider > int(cur_dividend):
                break
            cur_divider += divider

        if cur_divider == 0:
            return answer

        shift += len(cur_dividend) - len(str(cur_divider))

        if first_time:
            answer += (shift * " " + str(cur_divider) + (len(str(dividend)) - dividend_used) * " " + "|" + str(dividend // divider)) + "\n"
            first_time = False
        else:
            answer += (shift * " " + str(cur_divider)) + "\n"

        cur_dividend = str(int(cur_dividend) - cur_divider)

        shift += len(str(cur_divider)) - len(cur_dividend)


def main():
    print(long_division(int(sys.argv[1]), int(sys.argv[2])))


if __name__ == '__main__':
    main()
