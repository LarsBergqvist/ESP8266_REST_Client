'use strict'
const express = require('express'),
      fileExists = require('file-exists'),
      bodyParser = require('body-parser'),
      app = express();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

// Example : curl -i http://localhost:1010/api/LedState/2
app.get('/api/LedState/:led_id', function(req,res) {
    var ledState = 0;
    if (fileExists('led' + req.params.led_id)) {
        ledState = 1;
    }

    res.status(200).json({ "ledstate" : ledState });
});

// curl -i -H "Content-Type: application/json" -X PUT -d '{"count":"3"}' http://localhost:1010/api/ButtonPressCount/2
app.put('/api/ButtonPressCount/:button_id', function(req,res) {
    var count = 0;
    if (req.body.count) {
        count = req.body.count;
    }
    console.log("Button " + req.params.button_id + " has been pressed " + count + " times");
    res.status(200).json({ "buttoncount" : count });

});

app.listen(1010, function() {
    console.log("ready...");
});
