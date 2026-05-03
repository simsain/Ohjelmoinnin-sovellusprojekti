const express = require('express');
const router = express.Router();
const user = require('../models/user_model');

router.get('/',
 function(request, response) {
    user.getAll(function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    })
  });


router.get('/:uname',
 function(request, response) {
    user.getOne(request.params.uname, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
});

router.post('/', 
function(request, response) {
  user.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult); 
    }
  });
});

router.delete('/:uname', 
function(request, response) {
  user.delete(request.params.uname, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:uname', 
function(request, response) {
  user.update(request.params.uname, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;