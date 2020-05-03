const bsconfig = require('./bsconfig.json');
const Dotenv = require("dotenv-webpack");

const transpileModules = ["bs-platform"].concat(bsconfig["bs-dependencies"]);
const withTM = require("next-transpile-modules")(transpileModules);

const config = {
    webpack: (config, { buildId, dev, isServer, defaultLoaders, webpack }) => {
    // Add the new plugin to the existing webpack plugins
    config.plugins.push(new Dotenv({ silent: true }));

    return config;
  },
  target: 'serverless',
  pageExtensions: ["jsx", "js", "bs.js"],
};

module.exports = withTM(config);