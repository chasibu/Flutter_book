= ログイン機能の実装をしよう

現在の設定では、Cloud Firestoreに入力された貸し借りデータは誰でも確認して、編集することができます。
このままでは、秘密にしたいことも公開されてしまい困ってしまいます。

そこでログイン機能を実装し、自分が入力したデータは自分だけが見れるようにします。

この章を完了すると下記のタグの内容になります。

@<href>{https://github.com/chasibu/kasikari_memo/releases/tag/chapter12}

== ログイン機能の作成

ログイン機能の実装はFirebaseが提供している、「Firebase Authentication」を利用します。

=== Firebase Authenticationとは

自前で作ると大変な認証機能を少しのコードを追加するだけで動かすことができるサービスです。

 * メールアドレス・パスワード
 * 電話番号（SMS）
 * Google
 * Playゲーム
 * Facebook
 * Twitter
 * GitHub
 * 匿名ログイン

Firebase Authenticationを使うと簡単な設定でアプリにさまざまなログインをできるようになります。

今回のアプリではメールアドレス・パスワードと匿名ログインを使用します。

これからどのような設定でメールアドレス・パスワードと匿名ログインを使用できるのか説明していきます。

=== Firebase Authenticationの設定

コードを書く前に、FirebaseのWebコンソール上から設定を行います。

1.FirebaseのサイドメニューにあるAuthenticationをクリックします。

//image[open_authentication][Authenticationの開き方][scale=0.8]{
//}

2.ログインプロバイダからメールアドレス・パスワードを選択し、有効に変更して保存をクリックします。

//image[mail][メールアドレス・パスワードの有効化][scale=0.8]{
//}

3.ログインプロバイダから匿名を選択し、有効に変更して保存をクリックします。

//image[anonymous][匿名の有効化][scale=0.8]{
//}

4.メールアドレス・パスワード、匿名が有効になっていることを確認できれば大丈夫です。

//image[complete][メールアドレス・パスワード、匿名有効化の確認][scale=0.8]{
//}

これでFirebase側の準備は整いました。
それでは実際にコードを書いて行きましょう。

=== ライブラリの追加
//list[main_login1][pubspec.yaml][scale=0.8]{
  name: kasikari_memo
  description: kasikari memo Flutter application.
  ...
  dependencies:
    flutter:
      sdk: flutter
    cloud_firestore: ^0.7.3
    /*---------- Add Start ----------*/
    firebase_auth: ^0.5.20
    fluttertoast: ^2.0.7
    /*---------- Add End ----------*/

    cupertino_icons: ^0.1.2

  dev_dependencies:
    flutter_test:
      sdk: flutter
  ...
//}

ログイン機能を有効化するため@<code>{dependencies:}にライブラリを追加します。

 * @<code>{firebase_auth: ^0.5.20} : Firebase Authenticationを有効にします。
 * @<code>{fluttertoast: ^2.0.7} : ログインできなかったときにトースト表示をします。

=== ビルドエラー修正

//list[maim_login2][android/app/build.gradle]{
  ...
  android {
    compileSdkVersion 27

    defaultConfig {
        applicationId "local.chasibu.kasikarimemo"
        ...
        /*---------- Add Start ----------*/
        multiDexEnabled true
        /*---------- Add End ----------*/
    }
}
dependencies {
    ...
    implementation 'com.google.firebase:firebase-core:16.0.1'
    /*---------- Add Start ----------*/
    implementation 'com.android.support:multidex:1.0.3'
    /*---------- Add End ----------*/
}
//}

ライブラリーを追加した状態でビルドするとエラーが発生します。

その対応で「android/app/build.gradle」に上の2行を追記します。

=== ルーティングの変更
//list[main_login4][main.dart]{
import 'package:flutter/material.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
import 'dart:async';
/*---------- Add Start ----------*/
import 'package:firebase_auth/firebase_auth.dart';
import 'package:fluttertoast/fluttertoast.dart';
/*----------- Add End -----------*/
...
class MyApp extends StatelessWidget {
    @override
    Widget build(BuildContext context) {
      return new MaterialApp(
        title: 'かしかりメモ',
        /*---------- Add Start ----------*/
        routes: <String, WidgetBuilder>{
          '/': (_) =>  Splash(),
          '/list': (_) => List(),
        },
        /*---------- Add End ----------*/
      );
    }
  }
//}

今回のログインを作成するために次の2つのパッケージを追加します。

 * @<code>{package:firebase_auth/firebase_auth.dart}
 * @<code>{package:fluttertoast/fluttertoast.dart}

ログイン機能を実装する前に、ルーティングの設定を変更します。
アプリ起動時のデータを読み込む時間を待つために簡易スプラッシュ画面の実装を行います。

@<code>{MaterialApp}の@<code>{routes:}に対して、2つのルートを設定します。

 * @<code>{/} : スプラッシュ画面を表示
 * @<code>{/list} : リスト画面を表示

=== スプラッシュ画面の表示

//list[main_login5][main.dart]{

/*---------- Add Start ----------*/
FirebaseUser firebaseUser;
final FirebaseAuth _auth = FirebaseAuth.instance;

class Splash extends StatelessWidget{
  @override
  Widget build(BuildContext context) {
    _getUser(context);
    return Scaffold(
      body: Center(
        child: const Text("スプラッシュ画面"),
      ),
    );
  }
}

void _getUser(BuildContext context) async {
  try {
    firebaseUser = await _auth.currentUser();
    if (firebaseUser == null) {
      await _auth.signInAnonymously();
      firebaseUser = await _auth.currentUser();
    }
    Navigator.pushReplacementNamed(context, "/list");
  }catch(e){
    Fluttertoast.showToast(msg: "Firebaseとの接続に失敗しました。");
  }
}
/*---------- Add End ----------*/

//}
@<code>{_getUser()}を作成し、ログイン済みのユーザなのかの認証を行います。
ログイン済みじゃない場合、匿名ユーザを生成してログインします。

ユーザ情報の確認が終わると一覧画面に遷移します。

また、@<code>{Scaffold}内でスプラッシュ画面に実際に表示する内容を記載しており、
今回は画面の中央に「スプラッシュ画面」と表示しています。

=== ログインボタンの実装

//list[main_login6][main.dart]{
class _MyList extends State<List> {
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
          title: const Text("リスト画面"),
          actions: <Widget>[
            // action button
            /*---------- Add Start ----------*/
            IconButton(
              icon: Icon(Icons.exit_to_app),
              onPressed: () {
              print("login");
              showBasicDialog(context);
              },
            )
            /*---------- Add End ----------*/
          ]
      ),
      ...
      );
    }
  }
//}

ログインボタンは一覧画面の@<code>{appBar}に追記します。

これから実装する@<code>{showBasicDialog()}が呼び出され、ログイン画面を表示します。

=== ログイン画面の実装

//list[main_login7][main.dart]{
class _MyList extends State<List> {
  ...
}
/*---------- Add Start ----------*/
void showBasicDialog(BuildContext context) {
  final GlobalKey<FormState> _formKey = GlobalKey<FormState>();
  String email, password;
  if(firebaseUser.isAnonymous) {
    showDialog(
      context: context,
      builder: (BuildContext context) =>
          AlertDialog(
            title: Text("ログイン/登録ダイアログ"),
            content: Form(
              key: _formKey,
              child: Column(
                children: <Widget>[
                  TextFormField(
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
                  TextFormField(
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
              FlatButton(
                  child: const Text('キャンセル'),
                  onPressed: () {
                    Navigator.pop(context);
                  }
              ),
              FlatButton(
                  child: const Text('登録'),
                  onPressed: () {
                    if (_formKey.currentState.validate()) {
                      _formKey.currentState.save();
                      _createUser(context,email, password);
                    }
                  }
              ),
              FlatButton(
                  child: const Text('ログイン'),
                  onPressed: () {
                    if (_formKey.currentState.validate()) {
                      _formKey.currentState.save();
                      _signIn(context,email, password);
                    }
                  }
              ),
            ],
          ),
    );
  }else{
    showDialog(
      context: context,
      builder: (BuildContext context) =>
          AlertDialog(
            title: const Text("確認ダイアログ"),
            content: Text(firebaseUser.email + " でログインしています。"),
            actions: <Widget>[
              FlatButton(
                  child: const Text('キャンセル'),
                  onPressed: () {
                    Navigator.pop(context);
                  }
              ),
              FlatButton(
                  child: const Text('ログアウト'),
                  onPressed: () {
                    _auth.signOut();
                    Navigator.pushNamedAndRemoveUntil(context, "/", (_) => false);
                  }
              ),
            ],
          ),
    );
  }
}

void _signIn(BuildContext context,String email, String password) async {
  try {
    await _auth.signInWithEmailAndPassword(email: email, password: password);
    Navigator.pushNamedAndRemoveUntil(context, "/", (_) => false);
  }catch(e){
    Fluttertoast.showToast(msg: "Firebaseのログインに失敗しました。");
  }
}

void _createUser(BuildContext context,String email, String password) async {
  try {
    await _auth.createUserWithEmailAndPassword(email: email, password: password);
    Navigator.pushNamedAndRemoveUntil(context, "/", (_) => false);
  }catch(e){
    Fluttertoast.showToast(msg: "Firebaseの登録に失敗しました。");
  }
}
/*---------- Add End ----------*/
//}

@<code>{firebaseUser.isAnonymous}を使用し、ユーザが匿名アカウントか永久アカウントかで処理を分けます。

アプリ起動時にユーザがログインを行なっていない場合、匿名アカウントでアプリを使用します。

ログインボタンを押したときに、ログイン状態によって表示を切り替えます。

 * 匿名アカウントの場合 : ログインボタンを押すと、ログイン/登録画面が表示します。
 * 匿名アカウント以外の場合 : ログアウトボタンを表示します。

@<code>{_signIn}では、@<code>{_auth.signInWithEmailAndPassword}を使用し、メールアドレス・パスワードでログインします。

@<code>{_createUser}では、@<code>{_auth.createUserWithEmailAndPassword}を使用し、メールアドレス・パスワードで新規ユーザを作成します。

== Cloud Firestore と ログイン機能を組み合わせよう

=== データ保存構成

今までの機能では、次のような構成になっていました。

//image[structure_before][今までの構成][scale=0.6]{
//}

それを次のような構成に変更します。

users → [userID] → transaction → [貸し借りデータ]

 * userID : ログインしたユーザID
 * 貸し借りデータ : アプリから入力したデータ

//image[structure_after][今後の構成][scale=0.8]{
//}

====[column] Cloud Firestoreのデータ保存の仕組み

Cloud FirestoreではNoSQLドキュメント指向データベースです。
NoSQLはSQLとは異なり、キーと値の組み合わせ（key-value型）でデータの保存を行います。

データの集合をドキュメントという名称で呼び、ドキュメントの集合をコレクションという名称で呼びます。

//image[collection][データ、ドキュメント、コレクションの関係][scale=0.5]{
//}

また、ドキュメントの下にはデータだけなく、コレクションを追加することが可能です。
次の画像のように「コレクション→ドキュメント→コレクション...」という入れ子構造を作ることが可能です。

※ドキュメントの下にドキュメント、コレクションの下にコレクションを作ることはできません。

//image[ireko][ドキュメント、コレクションの入れ子構造][scale=0.6]{
//}

====[/column]


=== 入力機能の変更

//list[main_login9][main.dart]{
class _MyInputFormState extends State<InputForm> {

    @override
  Widget build(BuildContext context) {
    DocumentReference _mainReference;
    /*----------- Add Start -----------*/
    _mainReference = Firestore.instance.collection('users')
                        .document(firebaseUser.uid).collection("transaction")
                        .document();
    /*----------- Add End -----------*/
    bool deleteFlg = false;
    if (widget.document != null) {
      if(_data.user == null && _data.stuff == null) {
        _data.borrowOrLend = widget.document['borrowOrLend'];
        _data.user = widget.document['user'];
        _data.stuff = widget.document['stuff'];
        _data.date = widget.document['date'];
      }
      /*----------- Add Start -----------*/
      _mainReference = Firestore.instance.collection('users')
                          .document(firebaseUser.uid).collection("transaction")
                          .document(widget.document.documentID);
      /*----------- Add End -----------*/
      deleteFlg = true;
    }
  }
}
//}

かしかりデータを保持するための、@<code>{Firestore.instance}の生成方法を変更します。

先ほど決めた「データ保存構成」に沿うように修正します。

@<code>{collection('users')} →　@<code>{document(firebaseUser.uid)} → @<code>{collection("transaction")}

上の順に設定することで準備は完了です。

=== 一覧表示画面の変更

//list[main_login10][main.dart]{
  class _MyList extends State<List> {
    Widget build(BuildContext context) {
      return Scaffold(
        appBar: AppBar(
          ...
        ),
        body: Padding(
          padding: const EdgeInsets.all(8.0),
          child: StreamBuilder<QuerySnapshot>(
            /*----------- Edit Start -----------*/
            stream: Firestore.instance.collection('users').document(firebaseUser.uid)
                      .collection("transaction").snapshots(),
            /*----------- Edit End -----------*/
            builder: (BuildContext context, AsyncSnapshot<QuerySnapshot> snapshot) {
              if (!snapshot.hasData) return const Text('Loading...');
              return ListView.builder(
                ...
                );
              }
          ),
        ),
      )
    }
  }
//}

先ほど決めた「データ保存構成」に沿うように修正します。

=== Cloud Firestoreルール設定

Cloud Firestoreにはアクセス制御のルールを設定できます。
このルールをきちんとすることで、不正なアクセスを防ぐことができて安全なデータベースにできます。

自分が作成したデータのみを見れるような設定をします。

1. Firebaseにログインし、「Database > ルール」を開きます。

//image[cloud][ルール設定画面][scale=0.8]{
//}

2. 次のコードに置き換えて、「公開」とかかれたボタンをクリックします。

//list[sec][Cloud Firestore ルール]{
service cloud.firestore {
  match /databases/{database}/documents {
    match /users/{userId}/promise/{file} {
      allow read,create,delete,update: if request.auth.uid == userId;
    }
  }
}
//}

//image[setting][ルール設定画面][scale=0.8]{
//}

これで設定は完了です。

==== ルール説明

上記のコードの見方は、
「/users/{userId}/promise/{file}」の条件に一致するデータで、
「if request.auth.uid == userId」の条件に一致する場合に限り、
読み込み/新規作成/削除/アップデートの許可をするコードになります。

 * request.auth.uid : リクエストがあったユーザーのIDを指します。
 * userId : ファイルのフォルダとして使用しているユーザーのIDを指します。

フォルダのユーザーIDとリクエストのあったユーザーIDが一致したときに読み書きの権限を許可するようになっています。

これで他のファイルの読み書きはできないのでバグなどで間違えて他人のデータが見えてしまうということはなくなりました。

これでCloud Firestoreルール設定は完了です！

====[column] ルールのテスト
Cloud Firestoreルール設定をするときには問題がないか確認しながら開発することができます。

シミュレータがあり、認証した状態やパスの設定、読み書きの状態などさまざまなことを確認できるので開発時には使用しましょう！

//image[check][ルール設定画面][scale=0.5]{
//}

====[/column]


=== アプリを実行してみよう

アプリを実行して次の画像のように実際にログインフォームを入力し、アカウントを作成してログインしてみましょう。

//image[login][ログイン入力画面][scale=0.9]{
//}

これで本書の内容は完了です！！

エラー処理やテストなど本書で行うことができなかった項目はあるものの、
初めのFlutterを始めるきっかけとしてよかったのではないでしょうか？

今後の課題として何個か課題をあげるので興味があればぜひ試してみてください。

 * GoogleやFacebookなど他の認証でログインする
 * 期限になったらPush通知をする
 * グループ編集機能を作成する

ここまで本書を読み進めていただいてありがとうございました！！
