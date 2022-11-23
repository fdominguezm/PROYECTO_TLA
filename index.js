const { Client } = require('pg')

const connectionData = {
  username: 'benjamacbook',
  password: '427027',
  database: 'prueba_tla',
  host: 'localhost',
  port: 5432
}

const client = new Client(connectionData)

client.connect().then()

client.query('SELECT * FROM auto', (err, res) => {
  console.log(err ? err.stack : res) // Hello World!
})

client.query("INSERT INTO auto(modelo, marca) VALUES (2002, 'gol')", (err, res) => {
  console.log((err ? err.stack : res))
})

client.query('SELECT * FROM auto', (err, res) => {
  console.log(err ? err.stack : res.rows) // Hello World!
})

client.query('delete from auto', (err, res) => {
  console.log(err ? err.stack : res);
  client.end()
})

