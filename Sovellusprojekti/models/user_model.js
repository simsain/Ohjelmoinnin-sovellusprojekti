const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds=10;
const user={
  getAll: function(callback) {
    return db.query('select * from user', callback);
  },
  getOne: function(uname, callback) {
    return db.query('select * from user where username=?', [uname], callback);
  },
  add: function(user, callback) {
    bcrypt.hash(user.password, saltRounds, function(err, hash) {
      if (err) { 
        return callback(err.message);
      }
      return db.query('insert into user (username, password) values(?,?)',
      [user.username, hash], callback);
    });
  },
  delete: function(uname, callback) {
    return db.query('delete from user where username=?', [uname], callback);
  },
  update: function(uname, user, callback) {
    bcrypt.hash(user.password, saltRounds, function(err, hash) {
      if (err) { 
        return callback(err.message);
      }
      return db.query('update user set username=?, password=? where username=?',
      [user.username, hash, uname], callback);
    });
  },
  checkPassword: function(username, callback) {
  return db.query('SELECT password FROM user WHERE username = ?',[username], callback); 
}

}

          
module.exports = user;