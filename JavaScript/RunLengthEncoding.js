/*
Кодирует с помощью Jump-кодировки или Escape-кодировки и декодирует из них
*/


let codingType = process.argv[2];
let operationType = process.argv[3];
let inPutTxt = process.argv[4];
let outPutTxt = process.argv[5];

let fs = require('fs');

if ( (!process.argv[2]) & (process.argv[2] != '-e') & (process.argv[2] != '--escape') & (process.argv[2] != '-j') & (process.argv[2] != '--jump') ) {
    console.log()
    console.log(`Введите тип кодироваиня`)
    console.log('-e ИЛИ --escape для Escape-кодирования ИЛИ')
    console.log('-j ИЛИ --jump для Jump-кодирования')
    console.log()
    return -1;
}

if ( (!process.argv[3]) & (process.argv[3] != '-e') & (process.argv[3] != '--encode') & (process.argv[3] != '-d') & (process.argv[3] != '--decode') ) {
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

function escapeCode(count, sym) {
    return 
}

if ( ( (codingType == '--jump') || (codingType == '-j') ) & ( (operationType == '--decode') || (operationType == '-d') ) ) {
  
    let file = fs.readFileSync(inPutTxt, 'utf8');
    let result = '';
    num = 0;
  
    while (num < file.length - 1) {
        if (file.charCodeAt(num) > 127) {
            for (let i = 0; i < file.charCodeAt(num) - 127; i++) {
                result = result + file[num + 1]; }
            num += 2;
            continue
        }
        if (file.charCodeAt(num) <= 127) {
            let numconst = num;
            num++
            for (let i = 0; i < file.charCodeAt(numconst) + 1; i++) {
                result = result + file[num];
                num++
            }
            continue
        }
    } 
    fs.writeFileSync( outPutTxt, result);
}

if ( ( (codingType == '--jump') || (codingType == '-j') ) & ( (operationType == '--encode') || (operationType == '-e') ) ) {
  
    let file = fs.readFileSync(inPutTxt, 'utf8');
    let count = 0
    let str = '';
    let result = '';
  
    for (let i = 0; i < file.length; i++) {

        if (str == '') {
            str = file[i];
            count = 1;
            continue;
        }
        if (str.length == 1) {
            if (str != file[i]) str = 'n' + str + file[i];
            else str = 'r' + str;
            count = 2;
            continue;
        }
    
        if (str[0] == 'r') {
            if (file[i] != str[1]) {
                result = result + String.fromCharCode(count + 127) + str[1];
                str = file[i];
                count = 1;
            }
            if (file[i] == str[1]) count++
            if (count == 128) { 
                result = result + String.fromCharCode(count + 127) + str[1];
                str = '';
                count = 0;
            }
        }

        if (str[0] == 'n') {
            if (file[i] == file[i-1]) {
                str = str.slice(1,-1);
                result = result + String.fromCharCode(count - 2) + str;
                str = 'r' + file[i-1] + file[i];
                count = 2;
            }
            if (file[i] != file[i-1]) {count++; str = str + file[i]}
            if (count == 128) {
                str = str.slice(1,);
                result = result + String.fromCharCode(count - 1) + str;
                str = '';
                count = 0;
            }
        }
    }
    if (str) {
        if (str[0] == "n") result = result + String.fromCharCode(count - 1) + str.slice(1,);
        if (str.length == 1) result = result + String.fromCharCode(0) + str[0];
        if (str[0] == "r")  result = result + String.fromCharCode(count + 127) + str[1];
    }
    fs.writeFileSync( outPutTxt, result);
}

if ( ( (codingType == '--escape') || (codingType == '-e') ) & ( (operationType == '--encode') || (operationType == '-e') ) ) {

    let file = fs.readFileSync(inPutTxt, 'utf8');
    let repeat = file[0];
    let result = '';
    
    for (let i = 1; i < file.length; i++) {
        // console.log(repeat.length);
        if ((file[i] != repeat.slice(-1,)) & ((repeat.length > 3) || (repeat.slice(-1,) == '#')))    {
            if (repeat.slice(-1,) != '#') 
                result = result + '#' + String.fromCharCode(repeat.length - 4) + repeat.slice(-1,);
            else result = result + '#' + String.fromCharCode(repeat.length - 1) + repeat.slice(-1,);
            repeat = file[i];
            continue
        }
        
        if ((file[i] != repeat.slice(-1,)) & (repeat.length < 4)) {
            result = result + repeat
            repeat = file[i];
            continue
        }
        
        if (file[i] == repeat.slice(-1,)) repeat = repeat + file[i];

        if ( (repeat.length == 259) & (repeat[0] != '#') ) {
            result = result + '#' + String.fromCharCode(repeat.length - 4) + repeat.slice(-1,);
            repeat = '';
            console.log("jigaishiro")
        }

        if ( (repeat.length == 256) & (repeat[0] == '#') ) {
            result = result + '#' + String.fromCharCode(repeat.length - 1) + repeat.slice(-1,);
            repeat = '';
        }

    }
    if ((repeat.length > 3) || (repeat[0] == '#')) {
        if (repeat.slice(-1,) != '#') 
            result = result + '#' + String.fromCharCode(repeat.length - 4) + repeat.slice(-1,);
        else result = result + '#' + String.fromCharCode(repeat.length - 1) + '#';
        repeat = '';
    }
    result = result + repeat
    fs.writeFileSync( outPutTxt, result);
}

if ( ( (codingType == '--escape') || (codingType == '-e') ) & ( (operationType == '--decode') || (operationType == '-d') ) ) {
  
    let file = fs.readFileSync(inPutTxt, 'utf8');
    let result = '';
    let i = 0;
    let j = 0;
  
    while (i < file.length) {
        if (file[i] != '#') result = result + file[i];
        else {
            if (file[i + 2] != '#') 
                for (j = 0; j < file.charCodeAt(i + 1) + 4; j++) {
                    result = result + file[i + 2]; 
                }
            else 
                for (j = 0; j < file.charCodeAt(i + 1) + 1; j++) {
                    result = result + file[i + 2]; 
            }
            i += 2;
        }
        i++;
    }
    fs.writeFileSync( outPutTxt, result);
}

console.log()
console.log('Получилось!')
console.log()
