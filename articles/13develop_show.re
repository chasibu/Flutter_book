= 一覧画面の実装

この章では先ほどFirebaseのCloud Firestoreに登録した貸し借りデータを表示する機能の実装を行いながら、FlutterのUIについて学んでいきます。

この章を完了すると下記のタグの内容になります。

@<href>{https://github.com/chasibu/kasikari_memo/releases/tag/chapter7}

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

//image[uiget][packages get実行][scale=0.7]{
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
              title: Text("【 " + (document['borrowOrLend'] == "lend"?"貸":
                        "借") +" 】"+ document['stuff']),
              subtitle: Text('期限 ： ' + document['date'].toString()
                        .substring(0,10) + "\n相手 ： " + document['user']),
            ),
          ]
      ),
    );
  }
}
/*----------- Add End -----------*/
//}

Firestoreから読み込んだデータをリスト表示するためのコードを作成しました。

実行すると次のような画面が表示されます。

//image[list][list表示][scale=0.7]{
//}

=== リスト表示解説


Flutterでは@<code>{void main()}からアプリが開始されます。
@<code>{runApp}に表示データを渡すことでアプリの画面を作成しています。

どのような順で呼び出されるのかは次の図をご覧ください。



Flutterでは多くは「StatefulWidget」か「StatelessWidget」のどちらかを継承してクラスを作成します。。
今回は表示されるCloud Firestoreの内容が変化するので、@<code>{StatefulWidget}クラスを継承していきます。

必要によってPaddingを使い、表示するWidgetに余白を指定します。

==== StreamBuilder

Cloud Firestoreからデータを取得し、表示する機能を@<code>{StreamBuilder<QuerySnapshot>()}の中で実装します。

 * @<code>{stream:}は、非同期で取得できるデータを指定します。
今回であれば、@<code>{Firestore.instance.collection('kasikari-memo').snapshots()}
と指定したパスのデータをCloud Firestoreから取得します。
 * @<code>{builder:}は、@<code>{stream:}に変化があったときに呼び出されます。
 今回は、データの受信されるまでは「Loading...」と表示し、データを取得し始めたら
 @<code>{ListView.builder}にデータを渡し、表示します。

データを取得した時の@<code>{ListView.builder}のプロパティは次のとおりです。

//table[ListView.builder][ListView.builderのプロパティ]{
プロパティ	値	説明
--------------------------------------------------------------
scrollDirection:	Axis.vertical	スクロールの方向を決める。
itemCount:	snapshot.data.documents.length	表示するアイテムの数を決める。
padding:	const EdgeInsets.only(top: 10.0)	アイテムのパディングを決定。
itemBuilder:	(context, index) => _buildListItem()	次の項目にて説明
//}

==== itemBuilder

一件ごとのCloud Firestoreのデータを@<code>{_buildListItem}関数に渡し、リストデータを作成しています。

@<code>{ListTile}で表示したい文字を引数として渡された@<code>{document["タイプ名"]}で取得し表示しています。


== 新規ボタン追加

新規ボタンを追加して次の章でデータを追加できるように準備します。

次のコードで「/*-- Add Start --*/」と「/*-- Add End --*/」コメントの間にあるコードを追加しましょう。

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

新規ボタンを表示するためのコードを作成しました。

実行すると次のような画面が表示されます。

//image[add][追加ボタン][scale=0.7]{
//}

=== 追加ボタン解説

@<code>{Scaffold}に@<code>{floatingActionButton:}を追加し、新規作成ボタンを追加します。

登録機能の実装は後ほど行うため、ここでは、ボタンを押した時の処理を記載する、@<code>{onPressed:}の
中には@<code>{print("新規作成ボタンを押しました");}とだけ記載します。

この状態で、アプリを実行すると、新規登録ボタンが表示されます。

== 編集ボタン追加

編集ボタンを追加して次の章でデータを編集できるように準備します。

次のコードで「/*-- Add Start --*/」と「/*-- Add End --*/」コメントの間にあるコードを追加しましょう。

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
              title: Text("【 " + (document['borrowOrLend'] == "lend"?"貸":
                              "借") +" 】"+ document['stuff']),
              subtitle: Text('期限 ： ' + document['date'].toString()
                              .substring(0,10) + "\n相手 ： " + document['user']),
            ),
            /*---------- Add Start ----------*/
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
            /*----------- Add End -----------*/
          ]
      ),
    );
  }
}
//}

準備ボタンを表示するためのコードを作成しました。

実行すると次のような画面が表示されます。

//image[edit][編集ボタン][scale=0.7]{
//}

=== 編集ボタン解説

@<code>{Column}の中に@<code>{ButtonTheme.bar}を追加し、編集画面へのボタンを設定します。

@<code>{child: const Text("へんしゅう")}でボタンで表示したい文字を指定します。

編集機能の実装は後ほど行うため、ここでは、ボタンを押した時の処理を記載する、@<code>{onPressed:}の
中には@<code>{print("編集ボタンを押しました");}とだけ記載します。


この状態で、アプリを実行すると、編集ボタンが表示されます。

これでリスト表示の作成は完了です！
