= 一覧画面の実装

この章では先ほどFirebaseに登録した貸し借りデータを表示する機能の実装を行いながら、FlutterのUIについて学んでいきます。

//lead{
この章を完了すると下記のタグの内容になります。
@<href>{https://github.com/chasibu/kasikari_memo/releases/tag/chapter7}
//}

== pubspec.yamlの変更
1. 「pubspec.yaml」を開き、次のように変更を加えます。

//list[pubspec-connectfirebase][pubspec.yamlの変更]{
  dependencies:
    flutter:
      sdk: flutter
    cloud_firestore: ^0.7.3     # new
//}

2. コンソール画面から次のコマンドを入力します。
//cmd{
flutter packages get
//}

もしくは、Android Studioの画面上から操作することができるのでそちらから行ってください。

//image[uiget][packages get実行][scale=0.6]{
//}

== リスト作成

「main.dart」に書かれているものを削除し、次のコードに変更してください。

//list[main_show1][main.dart]{
/*---------- Add Start ----------*/
import 'package:flutter/material.dart';
import 'package:cloud_firestore/cloud_firestore.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'かしかりメモ',
      home: List(),
    );
  }
}

class List extends StatefulWidget {
  @override
  _MyList createState() => _MyList();
}

class _MyList extends State<List> {

  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
          title: const Text("リスト画面"),
      ),
      body: Padding(
        padding: const EdgeInsets.all(8.0),
        child: StreamBuilder<QuerySnapshot>(
            stream: Firestore.instance.collection('kasikari-memo').snapshots(),
            builder: (BuildContext context, AsyncSnapshot<QuerySnapshot> snapshot) {
              if (!snapshot.hasData) return const Text('Loading...');
              return ListView.builder(
                scrollDirection: Axis.vertical,
                itemCount: snapshot.data.documents.length,
                padding: const EdgeInsets.only(top: 10.0),
                itemBuilder: (context, index) =>
                    _buildListItem(context, snapshot.data.documents[index]),
              );
            }
        ),
      ),
    );
  }

  Widget _buildListItem(BuildContext context, DocumentSnapshot document){
    return Card(
      child: Column(
          mainAxisSize: MainAxisSize.min,
          children: <Widget>[
            ListTile(
              leading: const Icon(Icons.android),
              title: Text("【 " + (document['borrowOrLend'] == "lend"?"貸":"借") +" 】"+ document['stuff']),
              subtitle: Text('期限 ： ' + document['date'].toString().
                        substring(0,10) + "\n相手 ： " + document['user']),
            ),
          ]
      ),
    );
  }
}
/*----------- Add End -----------*/
//}

=== アプリの動作

Firebaseから読み込んだデータをリスト表示するためのコードを作成しました。

実行すると次のような画面が表示されます。

Flutterでは@<code>{main()}からアプリが開始します。
今回のコードでは次の順番でクラスが実行されます。



6. @<code>{build()}内で@<code>{StreamBuilder<QuerySnapshot>}を実行。

7. @<code>{StreamBuilder<QuerySnapshot>}内で@<code>{_buildListItem}が呼び出され、Firestoreにある保存されている、データを表示。

文字で書くと長く、ややこしい感じがしますが、実際にコードを目で追ってみると、どのようなフローを経て
表示されるのかがよく分かると思います。

次に先ほど記載した、クラスの呼び出しについて、ステップごとに解説を記載します。

==== 4.について
呼び出される@<code>{list()}はFirestoreに格納しているデータを表示する機能を持ちます。
Firestoreから毎回データを取得し、画面に表示しています。その為、Firestoreのデータの状態により
表示される画面の内容が変化する為、@<code>{StatefulWidget}クラスを継承し、クラスを作成します。

==== 6.について
@<code>{_MyList}クラスの@<code>{build}メソッド内で@<code>{Scaffold}を使用し、画面の描写を行います。
@<code>{body:}にはPaddingを代入し、表示する貸し借り情報に対して余白を設けます。
Firestoreからデータを取得し、表示する機能は@<code>{StreamBuilder<QuerySnapshot>()}の中で実装します。

==== 7.について
@<code>{StreamBuilder}は@<code>{_buildListItem}を使用し、Firestoreから取得したデータを表示させます。
@<code>{stream:}は、非同期に接続しているstreamを代入し使用します。
非同期に接続するデータはFirestoreから@<code>{Firestore.instance.collection('コレクション名').snapshots()}
で入手することが可能です。
@<code>{builder:}内では@<code>{snapshot}がデータを持っていない状態（Firestoreからデータを取得している状態）では
「Loading...」と表示し、データを一件でも取得し始めたら、@<code>{ListView}の形式で表示しています。

データを取得した時の@<code>{ListView.builder}のプロパティは次のとおりです。
//table[ListView.builder][ListView.builderのプロパティ]{
プロパティ	値	説明
--------------------------------------------------------------
scrollDirection:	Axis.vertical	スクロールの方向を決める。
itemCount:	snapshot.data.documents.length	表示するアイテムの数を決める。
padding:	const EdgeInsets.only(top: 10.0)	アイテムのパディングを決定。
itemBuilder:	(context, index) => _buildListItem()	次の項目にて説明
//}

@<code>{_buildListItem}クラスでは引数として@<code>{DocumentSnapshot document}を設定し、@<code>{ListTile}を使用して
一件ごとの貸し借りの情報を表示しています。
@<code>{document["タイプ名"]}でFirestoreに登録してある、データを取得し表示しています。

この状態で、アプリを実行すると、テスト入力したデータがリストとなって表示されます。

== 新規ボタン追加
//list[main_show2][main.dart]{
class _MyList extends State<List> {

    Widget build(BuildContext context) {
      return Scaffold(
        appBar: AppBar(
            title: const Text("リスト画面"),
        ),
        body: Padding(
          ...
        ),
        /*---------- Add Start ----------*/
        floatingActionButton: FloatingActionButton(
            child: const Icon(Icons.check),
            onPressed: () {
              print("新規作成ボタンを押しました");
            }
        ),
        /*----------- Add End -----------*/
      );
    }
}
//}

@<code>{Scaffold}に@<code>{floatingActionButton:}を追加し、新規作成ボタンを追加します。
登録機能の実装は後ほど行うため、ここでは、ボタンを押した時の処理を記載する、”onPressed:”の
中には@<code>{print("新規作成ボタンを押しました");}とだけ記載します。

この状態で、アプリを実行すると、新規登録ボタンが表示されます。

== 編集ボタン追加
//list[main_show3][main.dart]{
class _MyList extends State<List> {
  ...

  Widget _buildListItem(BuildContext context, DocumentSnapshot document){
    return Card(
      child: Column(
          mainAxisSize: MainAxisSize.min,
          children: <Widget>[
            ListTile(
              leading: const Icon(Icons.android),
              title: Text("【 " + (document['borrowOrLend'] == "lend"?"貸":"借") +" 】"+ document['stuff']),
              subtitle: Text('期限 ： ' + document['date'].toString().
                              substring(0,10) + "\n相手 ： " + document['user']),
            ),
            ButtonTheme.bar(
                child: ButtonBar(
                  children: <Widget>[
                    FlatButton(
                        child: const Text("へんしゅう"),
                        onPressed: ()
                        {
                          print("編集ボタンを押しました");
                        }
                    ),
                  ],
                )
            ),
          ]
      ),
    );
  }
}
//}
@<code>{Column}の中に@<code>{ButtonTheme.bar}を追加し、編集画面へのボタンを設定します。
編集機能の実装は後ほど行うため、ここでは、ボタンを押した時の処理を記載する、@<code>{onPressed:}の
中には@<code>{print("編集ボタンを押しました");}とだけ記載します。

この状態で、アプリを実行すると、編集ボタンが表示されます。
