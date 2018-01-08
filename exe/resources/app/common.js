const $ = require('jquery');
const electron = require('electron');
const shared = electron.remote.getGlobal('shared');
const query = shared.query;
const nprogress = require('nprogress');

