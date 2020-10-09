const fs = require('fs');

const md = require('markdown-it')()
  .use(require('markdown-it-include'))
  .use(require('markdown-it-highlightjs'))
  .use(require('./import-code'))

const result = md.render(fs.readFileSync(process.stdin.fd, 'utf-8'));

process.stdout.write(result);
