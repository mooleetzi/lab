#!/usr/bin/env python3
# -*- coding: utf-8 -*-


__author__ = 'mooleetzi'


from app import app,db,authLogin,authToken
from flask import json,jsonify,request,abort,g,url_for,make_response,current_app
from app.models import *
from app.code import Code
from app.util import make_result
from flask_cors import cross_origin
from functools import reduce
from itsdangerous import TimedJSONWebSignatureSerializer,BadSignature,SignatureExpired


@authToken.verify_token
def verify_token(token):
    s = TimedJSONWebSignatureSerializer(
        current_app.config['SECRET_KEY']
    )
    try:
        data = s.loads(token)
        print(data)
    except BadSignature:
        return False
        # raise AuthFailed(msg='token不正确')

    except SignatureExpired:
        return False
        # raise AuthFailed(msg='token过期')
    uid = data['uid']
    return True


@app.route("/")
@authLogin.login_required
def index():
    return jsonify('Hello, %s' % g.user.username)






@app.route('/api/register/', methods = ['POST'])
def register():
    username = request.json.get('username')
    password = request.json.get('password')
    print(username,password)
    if username is None or password is None:
        abort(400) # missing arguments
    if User.query.filter_by(username = username).first() is not None:
        abort(400) # existing user
    user = User(username = username,role_id=2)
    user.hash_password(password)
    db.session.add(user)
    db.session.commit()
    return jsonify({ 'username': user.username })

@authLogin.verify_password
def verify_password(username_or_token, password):
    print('username_token',username_or_token,password)
    # first try to authenticate by token
    user = User.verify_auth_token(username_or_token)
    if not user:
        # try to authenticate with username/password
        user = User.query.filter_by(username = username_or_token).first()
        if not user or not user.verify_password(password):
            return False
    g.user = user
    return True


#真实自闭
# cross_origin必须加

@app.route('/api/login/')
@authLogin.login_required
@cross_origin()
def login():
    token = g.user.generate_auth_token()
    return jsonify({'token':token.decode('ascii')})

# @app.route('/api/token/')
# @authToken.login_required
# @cross_origin()
# def get_auth_token():
#     token = g.user.generate_auth_token()
#     return jsonify({ 'token': token.decode('ascii') })


def user_to_json(user):
    l=[]
    if isinstance(user,list):
        for i in user:
            l.append(user_to_json(i))
    elif isinstance(user,User):
        return {
            'username':user.username,
            'role':user.role.name
        }
    return l

@app.route('/api/users/')
@authLogin.login_required
@cross_origin()
def get_users():
    rs=User.query.all()
    return jsonify({'data':user_to_json(rs)})

