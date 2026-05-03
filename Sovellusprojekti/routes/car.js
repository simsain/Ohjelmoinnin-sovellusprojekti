const express = require('express');
const router = express.Router();
const car = require('../models/car_model');

router.get('/',
  function (request, response) {
    car.getAll(function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        console.log(dbResult);
        response.json(dbResult);
      }
    })
  });

  router.get('/:id',
  function (request, response) {
    car.getOne(request.params.id, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    })
  });

  router.post('/',
  function (request, response) {
    car.add(request.body, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  });

  router.delete('/:id',
  function (request, response) {
    car.delete(request.params.id, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  });

  router.put('/:id',
  function (request, response) {
    car.update(request.params.id, request.body, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  });
  
  module.exports = router;