= ログイン機能の実装をしよう
現在の状態では、@<code>{kasikari-memo}コレクションに入力されたデータは誰でもアクセス可能です。

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

== Cloud Firestoreのデータ保存の仕組みについて
Cloud FirestoreではNoSQLドキュメント指向データベースです。NoSQLはSQLとは異なり、
データや行はなく、キーと値の組み合わせ（key-value型）でデータの保存を行います。
Cloud Firestoreでは、データの集合をドキュメントという名称で呼び、ドキュメントの集合を
コレクションという名称で呼びます。
//image[collection][データ、ドキュメント、コレクションの関係]{
//}

また、ドキュメントの下にはデータだけなく、コレクションを追加することが可能です。
そのため、次の画像のように「ドキュメント→コレクション→ドキュメント...」という入れ子構造を作ることが可能です。
※逆にいうと,ドキュメントの下にドキュメント、コレクションの下にコレクションを作ることはできません。
//image[ireko][ドキュメント、コレクションの入れ子構造]{
//}

今までの機能では、次の画像のような構成になっていました。
//image[structure_before][今までの機能の構成]{
//}

今回ログオン機能を追加することで、Cloud Firestoreの構成は次の画像の通りになります。
//image[structure_after][今までの機能の構成]{
//}
ユーザに対して、直に貸し借りデータを紐づけたいのですが、先に記載したようにドキュメントの下にドキュメントを
紐づける事は出来ないので、間にコレクションを挟んでいます。

== ライブラリの追加
//list[main_login1][pubspec.yaml]{

  name: kasikari_memo
  description: kasikari memo Flutter application.

  # The following defines the version and build number for your application.
  # A version number is three numbers separated by dots, like 1.2.43
  # followed by an optional build number separated by a +.
  # Both the version and the builder number may be overridden in flutter
  # build by specifying --build-name and --build-number, respectively.
  # Read more about versioning at semver.org.
  version: 1.0.0+1

  environment:
    sdk: ">=2.0.0-dev.68.0 <3.0.0"

  dependencies:
    flutter:
      sdk: flutter
    cloud_firestore: ^0.7.3
    /*---------- Add Start ----------*/
    firebase_auth: ^0.5.20
    fluttertoast: ^2.0.7
    /*---------- Add End ----------*/

    # The following adds the Cupertino Icons font to your application.
    # Use with the CupertinoIcons class for iOS style icons.
    cupertino_icons: ^0.1.2

  dev_dependencies:
    flutter_test:
      sdk: flutter


  # For information on the generic Dart part of this file, see the
  # following page: https://www.dartlang.org/tools/pub/pubspec

  # The following section is specific to Flutter.
  flutter:

    # The following line ensures that the Material Icons font is
    # included with your application, so that you can use the icons in
    # the material Icons class.
    uses-material-design: true

    # To add assets to your application, add an assets section, like this:
    # assets:
    #  - images/a_dot_burr.jpeg
    #  - images/a_dot_ham.jpeg

    # An image asset can refer to one or more resolution-specific "variants", see
    # https://flutter.io/assets-and-images/#resolution-aware.

    # For details regarding adding assets from package dependencies, see
    # https://flutter.io/assets-and-images/#from-packages

    # To add custom fonts to your application, add a fonts section here,
    # in this "flutter" section. Each entry in this list should have a
    # "family" key with the font family name, and a "fonts" key with a
    # list giving the asset and other descriptors for the font. For
    # example:
    # fonts:
    #   - family: Schyler
    #     fonts:
    #       - asset: fonts/Schyler-Regular.ttf
    #       - asset: fonts/Schyler-Italic.ttf
    #         style: italic
    #   - family: Trajan Pro
    #     fonts:
    #       - asset: fonts/TrajanPro.ttf
    #       - asset: fonts/TrajanPro_Bold.ttf
    #         weight: 700
    #
    # For details regarding fonts from package dependencies,
    # see https://flutter.io/custom-fonts/#from-packages
//}

ログイン機能を有効化するために、@<code>{dependencies:}に@<code>{firebase_auth: ^0.5.20},
@<code>{fluttertoast: ^2.0.7}を追加します。


== ビルドエラー修正

//list[maim_login2][build.gradle]{
  def localProperties = new Properties()
  ...
  android {
    compileSdkVersion 27

    lintOptions {
        disable 'InvalidPackage'
    }
    defaultConfig {
        // TODO: Specify your own unique Application ID (https://developer.android.com/studio/build/application-id.html).
        applicationId "local.chasibu.kasikarimemo"
        minSdkVersion 16
        targetSdkVersion 27
        versionCode flutterVersionCode.toInteger()
        versionName flutterVersionName
        testInstrumentationRunner "android.support.test.runner.AndroidJUnitRunner"
        /*---------- Add Start ----------*/
        multiDexEnabled true
        /*---------- Add End ----------*/

    }
    buildTypes {
        release {
            // TODO: Add your own signing config for the release build.
            // Signing with the debug keys for now, so `flutter run --release` works.
            signingConfig signingConfigs.debug
        }
    }
}

flutter {
    source '../..'
}

dependencies {
    testImplementation 'junit:junit:4.12'
    androidTestImplementation 'com.android.support.test:runner:1.0.2'
    androidTestImplementation 'com.android.support.test.espresso:espresso-core:3.0.2'
    implementation 'com.google.firebase:firebase-core:16.0.1'
    /*---------- Add Start ----------*/
    implementation 'com.android.support:multidex:1.0.3'
    /*---------- Add End ----------*/

}
//}
ライブラリーを追加した状態でビルドするとエラーを発生させる為、gradleファイルに追記します。
追記対象のgradleファイルは次の画像のとおりです。

//image[gradle][編集対象のgradleファイルの場所][scale=0.6]{
//}



== パッケージのインポート
//list[main_login3][main.dart]{
  import 'package:flutter/material.dart';
  import 'package:cloud_firestore/cloud_firestore.dart';
  import 'dart:async';
  /*---------- Add Start ----------*/
  import 'package:firebase_auth/firebase_auth.dart';
  import 'package:fluttertoast/fluttertoast.dart';
  /*----------- Add End -----------*/

//}

ログイン機能を有効にする為に、@<code>{package:firebase_auth/firebase_auth.dart},
@<code>{package:fluttertoast/fluttertoast.dart}を追加します。
また、パッケージでは



== ルーティングの変更
//list[main_login4][main.dart]{
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

ログイン機能を実装する前に、ルーティングの設定を変更します。
アプリ起動時におけるデータの読み込み中に表示する画面をスプラッシュ画面と呼び、
今回、ログイン機能の実装と並行して、この画面の実装も行います。

@<code>{MaterialApp}の@<code>{routes:}に対して@<code>{/}@<code>{/list}のふたつのルートを設定します。
アプリを立ち上げると、@<code>{/}にアクセスするので、@<code>{Splash()}が実行されます。


== スプラッシュ画面の表示

//list[main_login5][main.dart]{

/*---------- Add Start ----------*/
  FirebaseUser firebaseUser;

class Splash extends StatelessWidget{
  @override
  Widget build(BuildContext context) {
    _getUser().then((user){
      firebaseUser = user;
      Navigator.pushReplacementNamed(context, "/list");
    }).catchError((onError){
      Fluttertoast.showToast(msg: "Firebaseとの接続に失敗しました。");
    }
    );
    return Scaffold(
      body: Center(
        child: const Text("スプラッシュ画面"),
      ),
    );
  }
}

Future<FirebaseUser> _getUser() async {
  FirebaseUser user = await _auth.currentUser();
  if(user == null) {
    await _auth.signInAnonymously();
    user = await _auth.currentUser();
  }
  return user;
}
/*---------- Add End ----------*/

//}
@<code>{_getUser()}を作成し,ログイン済みのユーザなのかの認証を行います。
ユーザ情報の確認が終わると一覧画面に遷移します。

また、@<code>{Scaffold}内でスプラッシュ画面に実際に表示する内容を記載しており、
今回は画面の中央に「スプラッシュ画面」と表示しています。


== ログインボタンの実装

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
ボタン選択後、@<code>{showBasicDialog()}が呼び出され、ログイン画面が表示されます。

==　ログイン処理の実装

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
                      _createUser(email, password)
                          .then((FirebaseUser user) =>
                           Navigator.pushNamedAndRemoveUntil(context, "/", (_) => false))
                          .catchError((e) {
                        Fluttertoast.showToast(msg: "Firebaseの登録に失敗しました。");
                      });
                    }
                  }
              ),
              FlatButton(
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
/*---------- Add End ----------*/
//}

@<code>{firebaseUser.isAnonymous}を使用し、ログインユーザが匿名ユーザかどうかで処理を分けています。
匿名ユーザとは、アプリに登録していなくても、セキュリティルールで保護されたページが利用可能なユーザです。
アプリ起動時、ユーザはユーザ登録（ログイン）を行なっていない為、匿名ユーザでアプリを使用します。
その後,ログインを行い、永久アカウントでアプリを使用します。

その為、匿名ユーザでの場合、ログインボタンを押すと、ログイン/登録画面が表示され、
匿名ユーザ以外（ログインした状態）では、ログアウトボタンが表示されます。

認証を行う@<code>{_auth},ユーザ登録を行う@<code>{_createUser}の機能については、次に説明を行います。

//list[main_login8][main.dart]{
  class _MyList extends State<List> {
    ...
  }

  void showBasicDialog(BuildContext context) {
    ...
  }

  /*---------- Add Start ----------*/
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
  /*----------- Add End -----------*/

//}
@<code>{_auth}では、@<code>{_auth.signInWithEmailAndPassword}を使用し、メールアドレス、パスワードを
元にして、ログイン機能を実現しています。

@<code>{_createUser}では、@<code>{_auth.createUserWithEmailAndPassword}を使用し、メールアドレス、パスワードを
元にして、新規ユーザを作成します。

== 入力機能の変更

//list[main_login9][main.dart]{
class _MyInputFormState extends State<InputForm> {

    @override
  Widget build(BuildContext context) {
    DocumentReference _mainReference;
    bool deleteFlg = false;
    if (widget.document != null) {
      if(_data.user == null && _data.stuff == null) {
        _data.borrowOrLend = widget.document['borrowOrLend'];
        _data.user = widget.document['user'];
        _data.stuff = widget.document['stuff'];
        _data.date = widget.document['date'];
      }
      /*----------- Add Start -----------*/
        _mainReference =Firestore.instance.collection('users').document(firebaseUser.uid).collection("transaction").document(widget.document.documentID);
      /*----------- Add End -----------*/
      deleteFlg = true;
    } else {
      /*----------- Add Start -----------*/
      _mainReference = Firestore.instance.collection('users').document(firebaseUser.uid).collection("transaction").document();
      /*----------- Add End -----------*/
    }
  }
}
//}

かしかりデータを入力するための、@<code>{Firestore.instance}の生成方法を変更します。
ユーザごとのコレクションを取得するため、取得対象のコレクションを@<code>{collection('users')}に変更します。
ドキュメントもユーザIDごとに取得するので、@<code>{document(firebaseUser.uid)}を使用し、
ユーザに紐付く@<code>{collection}を取得します。


== 一覧表示画面の変更

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
            /*----------- Add Start -----------*/
            stream: Firestre.instance.collection('users').document(firebaseUser.uid).collection("transaction").snapshots(),
            /*----------- Add End -----------*/
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
一覧に表示するデータもログインユーザに紐づいたものにする必要があるので、@<code>{document(firebaseUser.uid)}を使用して
データを取り出しを行います。


ここまで実装すると、ログイン機能が有効になります。
次の画像のように実際にログインしてみましょう。
//image[splash][スプラッシュ画面][scale=0.6]{
//}

//image[login_form][ログインフォーム][scale=0.6]{
//}

//image[login][ログイン入力][scale=0.6]{
//}

//image[dialog][ログイン後にログインボタンを選択すると表示される確認ダイアログ][scale=0.6]{
//}
