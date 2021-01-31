module.exports = {
  env: {
    commonjs: true,
    es2021: true,
    node: true,
  },
  extends: 'eslint:recommended',
  parserOptions: {
    ecmaVersion: 12,
  },
  rules: {
    'no-unused-vars': 0,
  },
};

module.exports = {
  ignorePatterns: ['/docs/'],
  env: {
    es2017: true,
    es2020: true,
    es6: true,
    node: true,
    commonjs: true,
    es2021: true,
  },
  extends: ['plugin:prettier/recommended'],
  parserOptions: {
    ecmaVersion: 12,
  },
  plugins: ['prettier', 'markdown'],
  rules: {
    'prettier/prettier': 'error',
    'spaced-comment': ['error', 'always'],
  },
};
