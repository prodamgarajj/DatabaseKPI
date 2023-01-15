import sqlalchemy
from sqlalchemy import create_engine
from sqlalchemy import MetaData, Table, Column, Integer, String, ForeignKey, DateTime, Boolean
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship, backref
from sqlalchemy.orm import sessionmaker

metadata = MetaData(schema="public")
Base = declarative_base()
engine = create_engine('postgresql://postgres:35171418@localhost/computerclub', echo=True)


class Table(Base):
    __tablename__ = 'Table'

    TableID = Column(Integer, primary_key=True)
    RoomID = Column(Integer, ForeignKey('Room.RoomID'))
    Number = Column(Integer)


class Room(Base):
    __tablename__ = 'Room'
    RoomID = Column(Integer, primary_key=True)
    Number = Column(Integer)


class Computer(Base):
    __tablename__ = 'Computer'
    ComputerID = Column(Integer, primary_key=True)
    TableID = Column(Integer, ForeignKey('Table.TableID'))
    Serial = Column(String(20))
    Number = Column(Integer)
    Brand = Column(String(20))


class Client(Base):
    __tablename__ = 'Client'
    ClientID = Column(Integer, primary_key=True)
    FullName = Column(String(20))
    RegDate = Column(DateTime(timezone=False))
    BirthDate = Column(DateTime(timezone=False))


class Session(Base):
    __tablename__ = 'Session'
    SessionID = Column(Integer, primary_key=True)
    ClientID = Column(Integer, ForeignKey('Client.ClientID'))
    TableID = Column(Integer, ForeignKey('Table.TableID'))
    StartDate = Column(DateTime(timezone=False))
    EndDate = Column(DateTime(timezone=False))
    Status = Column(Boolean)


makerSession = sessionmaker(bind=engine)
