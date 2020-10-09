const fs = require('fs');
const md = require('markdown-it')();

// group 1: language
// group 2: import file path
const fileRegex = /(\w+) file=(.+)/;
const defaultRender = md.renderer.rules.fence

const render = (tokens, idx, options, env, self) => {
  const token = tokens[idx]

  if (fileRegex.test(token.info)) {
    const group = token.info.match(fileRegex);

    token.info = group[1];
    token.content = fs.readFileSync(group[2], 'utf-8');
  }

  return defaultRender(tokens, idx, options, env, self);
}

const importCode = (md, opts) => {
  md.renderer.rules.fence = render
}

module.exports = importCode
