/*
Реализация кодировки Хаффмана, кодирует или декодирует
*/


let operationType  = process.argv[2];
let inPutTxt  = process.argv[3];
let outPutTxt  = process.argv[4];
let JSon  = process.argv[5];
  
let fs = require('fs');

if ( (!process.argv[2]) & (process.argv[2] != '-e') & (process.argv[2] != '--encode') & (process.argv[2] != '-d') & (process.argv[2] != '--decode') ) {
    console.log()
    console.log(`Введите тип кодироваиня`)
    console.log('-e ИЛИ --encode для кодирования ИЛИ')
    console.log('-d ИЛИ --decode для декодирования')
    console.log()
    return -1;
  }
  
if (!fs.existsSync(inPutTxt)) {
    console.log()
    console.log(`Нет никакого \"${inPutTxt}\"`)
    console.log('Введите существующий тхт файл, с которого нужно брать текст')
    console.log()
    return -1;
  }

if (!fs.existsSync(outPutTxt)) {
    console.log()
    console.log(`Нет никакого \"${outPutTxt}\"`)
    console.log('Введите существующий тхт файл, в который нужно вписывать текст')
    console.log()
    return -1;
  }
  
if (fs.readFileSync(inPutTxt, 'utf8') == '') {
    console.log()
    console.log(`В \"${inPutTxt}\" пусто, работать не с чем`)
    console.log()
    return -1;
  }

function sortin(frequency, n) {               //Сортировка
    let flag = true;
    let temp;                        
    while (flag) {
        flag = false;

        for (let i = 0; i < n; i++) 
            if (frequency[i].fr < frequency[i + 1].fr) {
                temp = frequency[i]; 
                frequency[i] = frequency[i + 1];
                frequency[i + 1] = temp;
                flag = true;
            }
    }
}



if ( (operationType == "-e") || (operationType == "--encode") ) {
    let file = fs.readFileSync(inPutTxt, 'utf8');

    let frequency = [];

    let flag;
    let n = 0;

    for (let i = 0; i < file.length; i++)    {     //Проверка частот символов
        flag = true
        for (let j = 0; frequency[j]; j++) 
            if (frequency[j].syms[0].char == file[i]) {
                frequency[j].fr++;
                flag = false;
                break;
            }
        if (flag) {
            frequency.push({ fr: 1, syms: [ {char: file[i],  code: ""} ]});
            n++;
        }
        
    }

    frequency.push({ fr: 1, syms: [ {char: "key",  code: ""} ]});

    sortin(frequency, n);

    let lastS = n;

    while (frequency[1].fr) {
        let i = 0;
        while (frequency[lastS].syms[i]) {
            frequency[lastS].syms[i].code = '1' + frequency[lastS].syms[i].code;
            i++;
        }

        i = 0;
        while (frequency[lastS - 1].syms[i]) {
            frequency[lastS - 1].syms[i].code = "0" + frequency[lastS - 1].syms[i].code;
            i++;
        }

        let temp = { fr: frequency[lastS].fr + frequency[lastS - 1].fr, syms: frequency[lastS].syms.concat(frequency[lastS - 1].syms) }
        frequency[lastS - 1] = temp;
        frequency[lastS].fr = 0;
        lastS--;
        sortin(frequency, n);
    }

    let result = '';
    i = 0;
    for (let i = 0; i < file.length; i++) {
        for (let j = 0; frequency[0].syms[j]; j++) 
            if (file[i] == frequency[0].syms[j].char) {
                result += frequency[0].syms[j].code;
                break;
            }
    }

    for (let j = 0; frequency[0].syms[j]; j++)
        if (frequency[0].syms[j].char == "key") {
            result += frequency[0].syms[j].code;
            break;
        }

    while (result.length % 8) 
        result += "1";

    let result2 = "";

    for (let i = 0; result[i]; i += 8) {
        result2 += String.fromCharCode(parseInt(result.slice(i, i+8), 2))
    }

    fs.writeFileSync(outPutTxt, result2);

    let decodeCodes = [];

    for (let i = 0; i < n + 1; i++) {
        decodeCodes.push({"char": frequency[0].syms[i].char, "code": frequency[0].syms[i].code});
    }

    fs.writeFileSync(JSon, JSON.stringify(decodeCodes, null, 1));

    console.log('Ну все')
}

if ( (operationType == "-d") || (operationType == "--decode") ) {
    let file = fs.readFileSync(inPutTxt, 'utf8');
    let codes = fs.readFileSync(JSon, 'utf8');
    let error = false;

    let translator = JSON.parse(codes);

    let end;
    for (let i = 0; i < translator.length; i++)
        if (translator[i].char == "key") 
            end = translator[i].code;

    let result = '';
    let temp = '';
    for (let i = 0; i < file.length; i++) {
        temp = (file.charCodeAt(i)).toString(2);
        while (8 - temp.length) temp = '0' + temp;
        result += temp;
    }

    let result2 = '';
    let current = '';
    let oi = -1;
    for (let i = 0; i < result.length; i++) {
        current += result[i];
        if (oi != -1) continue;
        if (current == end) {
            oi = i + 1;
            current = '';
        }
        for (let j = 0; j < translator.length; j++)
            if (current == translator[j].code) {
                result2 += translator[j].char;
                current = '';
            }
    }

    if (oi == -1) error = true;

    if (current != '1'.repeat(result.length - oi)) error = true;

    if (error) console.log('Не может быть расшифровано');

    else {
        fs.writeFileSync(outPutTxt, result2);
        console.log('Ну все');
    }
}











