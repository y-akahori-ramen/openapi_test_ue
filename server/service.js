
import { writeFile } from 'node:fs/promises';
import path from 'path'

export default class Service {
    #storageDir;

    constructor(storageDir) {
        this.#storageDir = storageDir;
        console.log("constructor");
        console.log(this.#storageDir);
    }

    handleHello(req, res) {
        console.log('handle hello request');
        res.json({ message: "hello from server." });
    }

    uploadFile(req, res) {
        console.log('handle uploadFile request');

        console.log(this.#storageDir);

        const safeFilename = req.body.filename.replace(/\.\.\//g, "");
        const saveFilePath = path.resolve(this.#storageDir, safeFilename);

        console.log(saveFilePath);

        writeFile(saveFilePath, req.body.base64data, { encoding: "base64" })
            .then(() => {
                res.json({ filename: req.body.filename });
            });

    }
}
