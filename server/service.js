
import { writeFile } from 'node:fs/promises';
import path from 'path'
import fsPromises from 'fs/promises'

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

    index(req, res) {
        fsPromises.readdir(this.#storageDir)
            .then((entries) => {
                let items = [];

                for (const entry of entries) {
                    if (entry === '.gitkeep') {
                        continue;
                    }
                    items.push({ name: entry, link: entry });
                }

                res.render('index.ejs', { items: items });
            });
    }
}

export { Service, toSafeFileName }