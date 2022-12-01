import { Sequelize, DataTypes } from 'sequelize';
const user = 'benjamacbook';
const host = 'localhost';
const database = 'prueba_tla';
const password = 'lapa';
const port = 5432;
const sequelize = new Sequelize(database, user, password,
{host, port, dialect: 'postgres', logging: (...msg) => console.log(msg)})
export { sequelize, DataTypes }