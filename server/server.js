import { Service } from './service.js'
import express from 'express';
import openapi from 'express-openapi';
import path from 'path'
import { fileURLToPath } from 'url';
import { program } from 'commander';

const __filename = fileURLToPath(import.meta.url);

program
  .option('-p, --port <value>', 'server port number', 3000);
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

const server = app.listen(options.port, () => {
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