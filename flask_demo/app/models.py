#!/usr/bin/env python3
# -*- coding: utf-8 -*-

' a user module '

__author__ = 'mooleetzi'

from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from app import app


db=SQLAlchemy(app)


class Role:

    __tablename__="Role"

    def __init__(self,id,name):
        self.name=name
        self.id = id

    name = db.Column(db.String(16),nullable=False)
    id = db.Column(db.INTEGER,primary_key=True)

    def __repr__(self):
        return "id:{}, name: {}".format(self.id,self.name)

class User:

    __tablename__ = 'User'

    def __init__(self,username,password,id,icon,role):
        self.username=username
        self.password=password
        self.id = id
        self.icon=icon
        self.role=role
    id = db.Column(db.INTEGER,primary_key=True)
    username = db.Column(db.String(16),nullable=False)
    password = db.Column(db.String(36),nullable=False)
    icon = db.Column(db.String(100),nullable=False,default='default.jpg')
    role_id = db.Column(db.INTEGER, db.ForeignKey("role.id"))

    #引用关系

    role=db.relationship('Role',backref="role")

    def __repr__(self):
        return "username: {}, id: {}, password: {}, icon: {}, role:"

