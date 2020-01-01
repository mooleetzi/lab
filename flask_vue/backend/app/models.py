#!/usr/bin/env python3
# -*- coding: utf-8 -*-



__author__ = 'mooleetzi'

from app import db, app

from passlib.apps import custom_app_context

from itsdangerous import TimedJSONWebSignatureSerializer as Serializer, SignatureExpired, BadSignature #token
from flask import abort


class Role(db.Model):

    __tablename__='role'

    name=db.Column(db.String(10),nullable=False)
    id=db.Column(db.INTEGER,primary_key=True)
    #这里的关系引用已经不是底层，而是flask定义的，所以参数为模型名
    #外键引用第一个参数为引用模型名，第二个为被引用调用的名字 此处为User.role
    users=db.relationship('User',backref='role')

    def __repr__(self):
        return "{}".format(self.name)

class User(db.Model):

    __tablename__="user"

    username=db.Column(db.String(32),unique=True,nullable=False,index=True)
    password=db.Column(db.String(128),nullable=False)
    id=db.Column(db.INTEGER,primary_key=True)
    # 外键考虑底层，使用表名
    role_id=db.Column(db.INTEGER,db.ForeignKey('role.id'))

    def __repr__(self):
        return "username: {}, role_name: {}".format(self.username,self.role)

    def hash_password(self, password):
        self.password = custom_app_context.encrypt(password)

    def verify_password(self, password):
        return custom_app_context.verify(password, self.password)
    #生成token 时间有限为1000min
    def generate_auth_token(self, expiration = 60000):
        s = Serializer(app.config['SECRET_KEY'], expires_in = expiration)
        return s.dumps({ 'id': self.id })

    @staticmethod
    def verify_auth_token(token):
        s = Serializer(app.config['SECRET_KEY'])
        try:
            data = s.loads(token)
        except SignatureExpired:
            return None # valid token, but expired
        except BadSignature:
            return None # invalid token
        user = User.query.get(data['id'])
        return user