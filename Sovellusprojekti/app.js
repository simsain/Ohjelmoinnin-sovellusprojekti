var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var app = express();

require('dotenv').config();

const jwt = require('jsonwebtoken');

const loginRouter = require('./routes/login');
const bookRouter = require('./routes/book');
const userRouter = require('./routes/user');
const carRouter = require('./routes/car');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/login', loginRouter); //login is not protected 


// Middleware function that verifies JWT token and blocks unauthorized requests
function authenticateToken(request, response, next) {
    const authHeader = request.headers['authorization'];
    if (!authHeader) {
      return response.sendStatus(401);
    }
    const token = authHeader.split(' ')[1];
    if (!token) {
      return response.sendStatus(401);
    }
    jwt.verify(token, process.env.MY_TOKEN, function(err, user) {
      if (err) {
        return response.sendStatus(403);
      }
      request.user = user;
      next();
    })
  }

app.use('/user', userRouter);
app.use('/car', carRouter);
app.use('/book', bookRouter);
app.use(authenticateToken); //all routes below this line are protected






module.exports = app;

app.listen(3000, () => {
  console.log('Server running on port 3000');
});
