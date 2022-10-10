import Service from './service.js'
import express from 'express';
import openapi from 'express-openapi';
import path from 'path'
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);

const service = new Service();
const app = express()

app.use(express.json({ limit: "512mb" }));

const apiFilePath = path.resolve(path.dirname(__filename), '../api.yaml');
openapi.initialize({
    app: app,
    apiDoc: apiFilePath,
    validateApiDoc: true,
    operations: {
        helloOperation: service.handleHello,
        uploadFile: service.uploadFile,
    }
});

const port = 3000
const server = app.listen(port, () => {
    console.log(`Listening on port ${port}`)
})

function shutdown() {
    console.log('Shutdown server...');
    server.close(() => {
        console.log('Shutdown complete.')
    })
}

process.on('SIGTERM', shutdown);
process.on('SIGINT', shutdown);