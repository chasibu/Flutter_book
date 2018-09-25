= ログイン機能の実装
現在の状態では、"kasikari-memo"コレクションに入力されたデータを見ることができてしまいます。
アプリを公開するにあたり、それでは、困ってしまいます。
そこで、ログイン機能を実装し、自分が入力したデータは自分だけが見れるような機能を実装します。

== ログイン機能について
ログイン機能の実装はFirebaseが提供している、”Authentication”機能を利用します。
本来、サーバサイド側で自前で用意する必要のある、認証機能を簡単に実現することができます。
コードを記述する前に、FirebaseのWebコンソール上から設定を行います。
具体的な手順は次のとおりです。
1.FirebaseのWebコンソール画面から左ペインにある”Authentication”を選択します。
//image[open_authentication][認証画面]{
//}

2.ログインプロバイダからメール/パスワードを選択し、有効化に変更した後、保存を選択します。
//image[mail][メール/パスワード]{
//}

3.ログインプロバイダから匿名を選択し、有効化に変更した後、保存を選択します。
//image[anonymous][匿名の有効化]{
//}

4.メール/パスワード、匿名が有効になっていれば問題ありません。
//image[complete][メール/パスワード、匿名有効化の確認]{
//}

以上で管理コンソール側の準備は整いました。それでは実際にコードを書いて行きましょう。

== コードの説明
ログイン機能を実装する前に、ルーティングの設定を変更します。
アプリ起動時におけるデータの読み込み中に表示する画面をスプラッシュ画面と呼び、今回この画面の実装も
行います。

//list[main_login1][main.dart]{
class MyApp extends StatelessWidget {
   @override
  Widget build(BuildContext context) {
     return MaterialApp(
       title: "貸し借りメモ",
       routes: <String, WidgetBuilder>{
         '/': (_) => new Splash(),
         '/list': (_) => new _List(),
       },
     );
  }
}
//}
”MaterialApp”のroutesに対してふたつのルートを設定します。
”/（ルート）”が優先されるので、”Splash()”が実行されます。

//list[main_login2][main.dart]{

import 'package:flutter/material.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
import 'dart:async';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:fluttertoast/fluttertoast.dart';

FirebaseUser firebaseUser;

class Splash extends StatelessWidget{
    @override
    Widget build(BuildContext context) {
      _getUser().then((user){
        Navigator.pushReplacementNamed(context, "/list");
      });
      return Scaffold(
        appBar: AppBar(
            title: const Text('かしかりメモ'),
        ),
        body: Center(
          child: new Text("スプラッシュ画面"),
        ),
      );
    }
}

Future<FirebaseUser> _getUser() async {
  final FirebaseUser user = await _auth.currentUser();
  if(user != null) {
    firebaseUser = user;
  }else{
    await _auth.signInAnonymously();
    firebaseUser = await _auth.currentUser();
  }
}
//}
ここでは、"_getUser()"クラスを作成しFirebaseから登録済みのユーザの有無および情報を取得します。
ユーザ情報の確認が終わると一覧画面に遷移します。
また、”Scaffold”内でスプラッシュ画面に実際に表示する内容を記載しており、
今回は画面の中央に「スプラッシュ画面」と表示しています。

//list[main_login3][main.dart]{
class _List extends StatelessWidget {

  Widget build(BuildContext context) {
  return Scaffold(
    appBar: AppBar(
      title: Text("いちらん"),
        actions: <Widget>[
          // action button
          IconButton(
            icon: Icon(Icons.exit_to_app),
            onPressed: () {
              print("login");
              showBasicDialog(context);
            },
          )
        ]
    ),
  ...
  )
  }
}
//}
ログインボタンは一覧画面に追記します。ボタン選択後、”showBasicDialog”が呼び出され、ログイン画面が表示されます。

//list[main_login4][main.dart]{
  void showBasicDialog(BuildContext context) {
  final GlobalKey<FormState> _formKey = new GlobalKey<FormState>();
  String email, password;
  if(firebaseUser.isAnonymous) {
    showDialog(
      context: context,
      builder: (BuildContext context) =>
      new AlertDialog(
        title: new Text("ログイン/登録ダイアログ"),
        content: new Form(
          key: _formKey,
          child: Column(
            children: <Widget>[
              new TextFormField(
                decoration: const InputDecoration(
                  icon: const Icon(Icons.mail),
                  labelText: 'Email',
                ),
                onSaved: (String value) {
                  email = value;
                },
                validator: (value) {
                  if (value.isEmpty) {
                    return 'Emailは必須入力項目です';
                  }
                },

              ),
              new TextFormField(
                obscureText: true,
                decoration: const InputDecoration(
                  icon: const Icon(Icons.vpn_key),
                  labelText: 'Password',
                ),
                onSaved: (String value) {
                  password = value;
                },
                validator: (value) {
                  if (value.isEmpty) {
                    return 'Passwordは必須入力項目です';
                  }
                  if(value.length<6){
                    return 'Passwordは6桁以上です';
                  }
                },
              ),
            ],
          ),
        ),

        // ボタンの配置
        actions: <Widget>[
          new FlatButton(
              child: const Text('キャンセル'),
              onPressed: () {
                Navigator.pop(context);
              }),
          new FlatButton(
              child: const Text('登録'),
              onPressed: () {
                if (_formKey.currentState.validate()) {
                  _formKey.currentState.save();
                  _createUser(email, password)
                      .then((FirebaseUser user) =>
                      　Navigator.pushNamedAndRemoveUntil(context, "/", (_) => false))
                      .catchError((e) {
                        Fluttertoast.showToast(msg: "Firebaseの登録に失敗しました。");
                  });
                }
              }),
          new FlatButton(
              child: const Text('ログイン'),
              onPressed: () {
                if (_formKey.currentState.validate()) {
                  _formKey.currentState.save();
                  _signIn(email, password)
                      .then((FirebaseUser user) =>
                      　Navigator.pushNamedAndRemoveUntil(context, "/", (_) => false))
                      .catchError((e) {
                        Fluttertoast.showToast(msg: "Firebaseのログインに失敗しました。");
                  });
                }
              })
        ],
      ),
    );
  }else{
    ・・・
  }
}

final FirebaseAuth _auth = FirebaseAuth.instance;

Future<FirebaseUser> _signIn(String email, String password) async {
  final FirebaseUser user = await _auth.signInWithEmailAndPassword(
      email: email, password: password);
  print("User id is ${user.uid}");
  return user;
}

Future<FirebaseUser> _createUser(String email, String password) async {
  final FirebaseUser user = await _auth.createUserWithEmailAndPassword(
      email: email, password: password);
  print("User id is ${user.uid}");
  return user;
}

//}
if(firebaseUser.isAnonymous) のelse文よりも前の箇所を記載します。
”showBasicDialog”呼び出し直後に、まず、すでにログイン済みなのかを
"firebaseUser.isAnonymous"を利用して確認します。
登録していないユーザであれば、メールとパスワード入力画面を表示させます。
登録ボタン選択後は、"_createUser"を実行し、記入したメールアドレス、パスワードを元にユーザを作成します。
ログインボタン選択後は、”_signIn”を実行し、記入したメールアドレス、パスワードを元にログインを行います。

ログイン済みのユーザに関しては、else文以降に処理を記載していますので、次で解説します。

//list[main_login6][main.dart]{
  void showBasicDialog(BuildContext context) {
  final GlobalKey<FormState> _formKey = new GlobalKey<FormState>();
  String email, password;
  if(firebaseUser.isAnonymous) {
    ...
　}else{
  showDialog(
  context: context,
  builder: (BuildContext context) =>
  new AlertDialog(
    title: new Text("確認ダイアログ"),
    content: new Text((firebaseUser.isAnonymous?"匿名ユーザー":firebaseUser.email) + " でログインしています。"),

    actions: <Widget>[
      new FlatButton(
          child: const Text('キャンセル'),
          onPressed: () {
            Navigator.pop(context);
          }),
      new FlatButton(
          child: const Text('ログアウト'),
          onPressed: () {
            _auth.signOut();
            Navigator.pushNamedAndRemoveUntil(context, "/", (_) => false);
          }),
    ],
  ),
  );
 }
}
//}
ログイン済みのユーザに対しては、”showDialog”を使用し、ログインユーザ名を表示します。
また、表示するボタンもキャンセルボタン、ログアウトボタンに仕様を変更します。

//list[main_login7][main.dart]{
class _MyInputFormState extends State<InputForm> {
  Widget build(BuildContext context) {
    var _mainReference;
    if (this.widget.docs != null) {
      if(lendorrent_Flg == 0 && widget.docs['lendorrent'].toString() == "lend"){
        lendorrent = "lend";
        lendorrent_Flg = 1;
      }
      _data.user = widget.docs['name'];
      _data.loan = widget.docs['loan'];
      print(date);
      if(change_Flg == 0) {
        date = widget.docs['date'];
      }
      _mainReference = Firestore.instance.collection('users').document(firebaseUser.uid).collection("kasikari-memo").document(widget.docs.documentID);
      deleteFlg = true;
    } else {
      _data.lendorrent = "";
      _data.user = "";
      _data.loan = "";
      _mainReference = Firestore.instance.collection('users').document(firebaseUser.uid).collection("kasikari-memo").document();
      deleteFlg = false;
    }
  }
}
//}
ログイン機能実装にあたり、”_MyInputFormState”内の"build"内も変更を加えます。
今までは、"_mainReference"に対して、コレクション"kasikari-memo"を取得していましたが、ログイン機能を加えたことで
ログインしたユーザが書き込んだデータのみを取得するような変更を加えています。


この状態でアプリを実行してみましょう。
問題なければ、スプラッシュ画面が表示され、その後に一覧画面が表示れるようになります。
また、画面上部にログインボタンが追加されています。
動作確認を兼ねて、新規登録をしてみましょう。

以上で、貸し借りメモアプリの完成です。お疲れさまでした。
