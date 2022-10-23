import { Service } from './service.js'
import express from 'express';
import openapi from 'express-openapi';
import path from 'path'
import { fileURLToPath } from 'url';
import { program } from 'commander';
import https from 'https'
import http from 'http'
import fs from 'fs'

const __filename = fileURLToPath(import.meta.url);

program
  .option('-p, --port <value>', 'server port number', 3000)
  .option('-key, --key <value>', 'private key file for tls')
  .option('-crt, --crt <value>', 'crt file for tls');
program.parse();
const options = program.opts();
  
const storageDir = path.resolve(path.dirname(__filename), 'saved');
const service = new Service(storageDir);

const app = express()
app.use(express.json({ limit: "512mb" }));

const apiFilePath = path.resolve(path.dirname(__filename), '../api.yaml');
openapi.initialize({
    app: app,
    apiDoc: apiFilePath,
    validateApiDoc: true,
    operations: {
        helloOperation: service.handleHello.bind(service),
        uploadFile: service.uploadFile.bind(service),
    }
});

const enableTLS = options.key !== undefined && options.crt !== undefined;
console.log(`enableTLS: ${enableTLS}`);

let server;
if(enableTLS)
{
    const tlsOptions = {
        cert: fs.readFileSync(options.crt),
        key: fs.readFileSync(options.key),
    }
    server = https.createServer(tlsOptions,app);
}
else
{
    server = http.createServer(app);
}

server.listen(options.port, () => {
    console.log(`Listening on port ${options.port}`)
})

function shutdown() {
    console.log('Shutdown server...');
    server.close(() => {
        console.log('Shutdown complete.')
    })
}

process.on('SIGTERM', shutdown);
process.on('SIGINT', shutdown);