
import { writeFile } from 'node:fs/promises';
import path from 'path'

function toSafeFileName(filename) {
    return filename.replace(/(\.\.\/|\.\.\\)/g, "");
}

class Service {
    #storageDir;

    constructor(storageDir) {
        this.#storageDir = storageDir;
    }

    handleHello(req, res) {
        res.json({ message: "hello from server." });
    }

    uploadFile(req, res) {
        // Prevent save file to upper directory
        const safeFilename = toSafeFileName(req.body.filename);
        const saveFilePath = path.resolve(this.#storageDir, safeFilename);

        console.log(`save image: ${saveFilePath}`);

        writeFile(saveFilePath, req.body.base64data, { encoding: "base64" })
            .then(() => {
                res.json({ filename: req.body.filename });
            });

    }
}

export { Service, toSafeFileName }