/*
Ищет подстроку в строки с помощью одного из трех алгоритмов
Перебор грубой силы, хэш суммой или хэшем Рабина-Карпа
Также выводит время работы и количество коллизий
*/


let opType = process.argv[2];
let mainString = process.argv[3];
let subString = process.argv[4];

let fs = require('fs');

let main = fs.readFileSync(mainString, 'utf8');
let sub = fs.readFileSync(subString, 'utf8');
let ansTime = 0;
let ansComps = 0;
let ansCollizes = 0;
let ansMatches = 0;
let indexMatches = [];

if (!main) 
  console.log(`В ${mainString} пусто`)

if (!sub)
  console.log(`В ${subString} пусто`)

if ((!sub) || (!main)) 
  return 0;

if (opType == "bruteforce") {
  let start = performance.now();

  for (i = 0; i <= main.length - sub.length; i++) {
    ansComps++;
    for (j = 0; j < sub.length; j++) {

        if (main[i + j] != sub[j]) break;
        if (j == sub.length - 1) {
          ansMatches++; 
          indexMatches.push(i);
        }
    }
  }

  ansTime = performance.now() - start;
}

function hashSum(str) {
  let hash = 0;
  for (z = 0; z < str.length; z++) {
    hash += str.charCodeAt(z);
  }
  
  return hash;
}

if (opType == "hashsum") {
    let start = performance.now();
  
    let subHash = hashSum(sub);
    let curHash = hashSum(main.slice(0, sub.length));

    for (i = 0; i <= main.length - sub.length; i++) {

      if (curHash == subHash) {
        ansComps++;

        for (j = 0; j < sub.length; j++) {
  
          if (main[i + j] != sub[j]) {
            ansCollizes++;
            break;
          }

          if (j == sub.length - 1) {
            ansMatches++; 
            indexMatches.push(i);
          }
        }
      }

      if (i != main.length - sub.length) {
        curHash -= hashSum(main[i]);
        curHash += hashSum(main[i + sub.length]);
      }
    }
  
    ansTime = performance.now() - start;
}
  
function rkHash(str) {
  let hash = 0;
  for (z = 0; z < str.length; z++) {
    hash += str.charCodeAt(z) * Math.pow(2, str.length - z - 1);
  }
  
  return hash % (Math.pow(2, 32) - 5);
}

if (opType == "hashrk") {
    let start = performance.now();
  
    let subHash = rkHash(sub);
    let curHash = rkHash(main.slice(0, sub.length));

    for (i = 0; i <= main.length - sub.length; i++) {

      if (curHash == subHash) {
        ansComps++;

        for (j = 0; j < sub.length; j++) {
  
          if (main[i + j] != sub[j]) {
            ansCollizes++;
            break;
          }

          if (j == sub.length - 1) {
            ansMatches++; 
            indexMatches.push(i);
          }
        }
      }

      if (i != main.length - sub.length) {
        curHash -= hashSum(main[i]) * Math.pow(2, (sub.length - 1));
        curHash *= 2; 
        curHash += hashSum(main[i + sub.length]);
      }
    }
  
    ansTime = performance.now() - start;
}

printAns();

function printAns() {
  console.log(`Время работы: ${ansTime} миллисекунд`)
  console.log(`Количество побуквенных сравнений: ${ansComps}`)
  console.log(`Количество коллизий: ${ansCollizes}`)
  console.log(`Количество совпадений: ${ansMatches}`)
  let answer = indexMatches.join(' ');
  if (answer)
    console.log(`Первые совпадения: ${answer}`)
}
