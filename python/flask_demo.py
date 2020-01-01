


# 1, 导入Flask扩展
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
import pymysql


# 2, 创建Flask应用实例

# 需要传入__name__ 作用是确定资源所在路径
app = Flask(__name__)

# 配置数据库地址
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://root:mysql981218@localhost/flask_demo'

app.config['SQLALCHEMY_COMMIT_ON_TEARDOWN'] = True
# 动态跟踪数据库修改 不建议开启 据说未来版本会移除
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

db=SQLAlchemy(app)

"""
两张表
角色(管理员/普通用户)
用户(id)
"""


class Role(db.Model):

    #定义表名
    __tablename__ = "roles"

    # 定义字段

    id = db.Column(db.INTEGER, primary_key=True)

    name = db.Column(db.String(16),unique=True)

    user=db.relationship('User',backref='Role')


class User(db.Model):

    __tablename__ = "users"

    id = db.Column(db.INTEGER, primary_key=True)

    name = db.Column(db.String(16), unique=True)
    # 外键定义
    role_id = db.Column(db.INTEGER, db.ForeignKey('roles.id'))


pymysql.install_as_MySQLdb()

# 删除表
db.drop_all()

# 创建表
db.create_all()

# role = Role(id=1,name="管理员")
#
# user=User(id=1,name='张三',role_id=1)
#
# db.session.add(role)
# db.session.add(user)
# db.session.commit()

# 3， 定义路由及视图函数

# 装饰器定义路由

# 默认路由只支持get 如需增加 需要自行指定
@app.route('/', methods=['get','post'])
def hello_world():
    return 'Hello World!'


# 路由传参,参数限制

@app.route('/user/<int:user_id>')
def user(user_id):
    return "你好 %d"%user_id



# 4，启动程序

if __name__ == '__main__':


    # 跑在简易服务器
    app.run()
