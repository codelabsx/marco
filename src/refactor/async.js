
fs.readFile(filename, (err, content) => {
    fs.writeFile(filename, content, err => {

    });

    setTimeout(() => {
        console.log('timer done!');
    });
});