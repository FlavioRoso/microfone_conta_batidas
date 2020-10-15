const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const port = new SerialPort('COM4', { baudRate: 9600 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));
const functions = {
  
    "EXEC" : data =>
    {
        exec(data);
    },
    "SHOW": data =>{
      console.log(data);
    }
}

let request = "";
let comand = "";
let data = "";

// Read the port data


const { exec } = require('child_process');



port.on("open", () => {
  console.log('Ouvindo Arduino....');
});
parser.on('data', rawData =>{
  
  request = rawData.split("->");
  
  comand = request[0].trim();
  data = request[1].trim();
  functions[comand](data);

});
