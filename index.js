import { Sequelize, Model, DataTypes } from 'sequelize';

const user = 'benjamacbook'
const host = 'localhost'
const database = 'prueba_tla'
const password = ''
const port = '5432'


const sequelize = new (database, user, password, {
  host,
  port,
  dialect: 'postgres',
  logging: (...msg) => consoleg.log(msg),
})

const Auto = sequelize.define('Autos', {
  marca: {
    type: DataTypes.STRING,
  },
  anio: {
    type: DataTypes.INTEGER,
  }
});

const mio = Auto.build({marca:"peugeot", anio:207});
await mio.save();