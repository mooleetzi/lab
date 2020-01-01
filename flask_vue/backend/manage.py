#!/usr/bin/env python3
# -*- coding: utf-8 -*-

' a test module '

from flask import Flask

from app import app
from flask_script import Manager
from flask_migrate import Migrate, MigrateCommand

from app.models import User,Role

from app import db

@app.route('/')
def hello_world():
    return 'Hello World!'



manager = Manager(app)

# 使用migrate绑定app和db
migrate = Migrate(app, db)

# 添加迁移脚本的命令到manager中
manager.add_command('db', MigrateCommand)

if __name__ == '__main__':
    manager.run()