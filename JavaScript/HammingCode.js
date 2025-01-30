/*
Реализация алгоритма кода Хемминга для четырех битов
Кодирует и декодирует число
При декодировании, может найти и исправить одну ошибку, или только сообщить о наличии двух ошибок
*/



let operationType  = process.argv[2];
let input = process.argv[3];

function i(x) {
    return x.charCodeAt() - 48 
}

function s(x) {
    return x.toString()
}

if (operationType == "-e" || operationType == "--encode") {

    if (input.length != 4) { 
        console.log("Неверное количество символов, должно быть 4")
        return 0;
    }

    let [d1, d2, d3, d4] = input;

    let p1 = (i(d2) + i(d3) + i(d4)) % 2;
    let p2 = (i(d1) + i(d3) + i(d4)) % 2;
    let p3 = (i(d2) + i(d1) + i(d4)) % 2;
    let p4 = (i(d1) + i(d2) + i(d3) + i(d4) + p1 + p2 + p3) % 2;

    console.log(s(p1) + s(p2) + s(d1) + s(p3) + s(d2) + s(d3) + s(d4) + s(p4));
    return 0;
}

function search(str) {
    c1 = "1010101"
    c2 = "0110011"
    c3 = "0001111"
    let ans = [0, 0, 0];

    for (let j = 0; j < 7; j++) {
        ans[0] += i(str[j]) * i(c1[j])
        ans[1] += i(str[j]) * i(c2[j])
        ans[2] += i(str[j]) * i(c3[j])
    }

    ans[0] %= 2;
    ans[1] %= 2;
    ans[2] %= 2;

    return parseInt(s(ans[0]) + s(ans[1]) + s(ans[2]), 2);
}

if (operationType == "-d" || operationType == "--decode") {

    if (input.length != 8) {
        console.log("Неверное количество символов, должно быть 8")
        return 0;
    }
    let c = input

    let z = [i(c[0]), i(c[1]), i(c[2]), i(c[3]), i(c[4]), i(c[5]), i(c[6]), i(c[7])]

    if (z[7] != (z[0] + z[1] + z[2] + z[3] + z[4] + z[5] + z[6]) % 2) {

        if (
            z[0] == (z[4] + z[5] + z[6]) % 2 &
            z[1] == (z[2] + z[5] + z[6]) % 2 &
            z[3] == (z[4] + z[2] + z[6]) % 2 
        ) {
            c = c.slice(0, 7) + s((i(c[7]) + 1) % 2);

            result = c[2] + c.slice(4,7);

            console.log(`В сообщении одна (1) ошибка - 8-й символ`)
            console.log(`Исправленная версия: ${c}`)
            console.log(`Результат: ${result}`)
            return 0;
        }
        
        let checkN = search(c);

        c = c.slice(0, checkN - 1) + s((i(c[checkN - 1]) + 1) % 2) + c.slice(checkN, 9)

        result = c[2] + c.slice(4,7);

        console.log(`В сообщении одна (1) ошибка - ${checkN}-й символ`)
        console.log(`Исправленная версия: ${c}`)
        console.log(`Результат: ${result}`)
        return 0;
    }

    if (
        z[0] != (z[4] + z[5] + z[6]) % 2 ||
        z[1] != (z[2] + z[5] + z[6]) % 2 ||
        z[3] != (z[4] + z[2] + z[6]) % 2 
    ) {
        console.log(`В сообщении сразу две (2) ошибки`)
        return 0;
    }

    console.log(`Ошибок не имеется`)
    console.log(`Результат: ` + c[2] + c[4] + c[5] + c[6])

    return 0;

}

else {
    console.log(`Нужен тип операции`)
    console.log('-e ИЛИ --encode для кодирования ИЛИ')
    console.log('-d ИЛИ --decode для декодирования')
}
