
import { writeFile } from 'node:fs/promises';

export default class Service {
    handleHello(req, res) {
        console.log('handle hello request');
        res.json({ message: "hello from server." });
    }

    uploadFile(req, res) {
        console.log('handle uploadFile request');

        writeFile(req.body.filename, req.body.base64data, { encoding: "base64" })
            .then(() => {
                res.json({ filename: req.body.filename });
            });
    }
}
