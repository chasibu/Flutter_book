= 編集機能の実装

この章では登録してあるデータの編集機能の実装を行います。

この章を完了すると下記のタグの内容になります。

@<href>{https://github.com/chasibu/kasikari_memo/releases/tag/chapter10}

== 編集機能の作成

編集を行うために引数として編集元のデータを渡せるように修正していきます。

次のコードで「/*-- Add Start --*/」と「/*-- Add End --*/」コメントの間にあるコードを追加、
「/*-- Edit Start --*/」と「/*-- Edit End --*/」コメントの間にあるコードを修正しましょう。

//list[main_update2][main.dart]{
  ...
  class _MyList extends State<List> {

    Widget build(BuildContext context) {
      return Scaffold(
        appBar: AppBar(
            title: const Text("リスト画面"),
        ),
        body: Padding(
          ...
        ),
        floatingActionButton: FloatingActionButton(
            child: const Icon(Icons.check),
            onPressed: () {
              print("新規作成ボタンを押しました");
              Navigator.push(
                context,
                MaterialPageRoute(
                    settings: const RouteSettings(name: "/new"),
                    /*---------- Edit Start ----------*/
                    builder: (BuildContext context) => InputForm(null)
                    /*----------- Edit End -----------*/
                ),
              );
            }
        ),
      );
    }

    Widget _buildListItem(BuildContext context, DocumentSnapshot document){
      return Card(
        child: Column(
            mainAxisSize: MainAxisSize.min,
            children: <Widget>[
              ...
              ButtonTheme.bar(
                  child: ButtonBar(
                    children: <Widget>[
                      FlatButton(
                          child: const Text("へんしゅう"),
                          onPressed: ()
                          {
                            print("編集ボタンを押しました");
                            /*---------- Add Start ----------*/
                            Navigator.push(
                              context,
                              MaterialPageRoute(
                                  settings: const RouteSettings(name: "/edit"),
                                  builder: (BuildContext context) => InputForm(document)
                              ),
                            );
                            /*----------- Add End -----------*/
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

  class InputForm extends StatefulWidget {
    /*---------- Add Start ----------*/
    InputForm(this.document);
    final DocumentSnapshot document;
    /*----------- Add End -----------*/

    @override
    _MyInputFormState createState() => _MyInputFormState();
  }

  class _MyInputFormState extends State<InputForm> {
    ...

    @override
    Widget build(BuildContext context) {
      /*---------- Add Start ----------*/
      DocumentReference _mainReference;
      _mainReference = Firestore.instance.collection('kasikari-memo').document();
      if (widget.document != null) {
        if(_data.user == null && _data.stuff == null) {
          _data.borrowOrLend = widget.document['borrowOrLend'];
          _data.user = widget.document['user'];
          _data.stuff = widget.document['stuff'];
          _data.date = widget.document['date'];
        }
        _mainReference = Firestore.instance.collection('kasikari-memo').document(widget.document.documentID);
      }
      /*----------- Add End -----------*/
      return Scaffold(
        appBar: AppBar(
          title: const Text('かしかり入力'),
          ...
        ),
      );
    }
  }
//}

これで編集ボタンを押したときにデータの更新ができるようになりました。実際に動かしてみましょう！

=== 編集機能の解説

次の4つの部分のコードを修正しました。順に説明していきます。

 * 引数の追加
 * 新規作成ボタンの修正
 * 編集ボタンの処理追加
 * 編集データの作成

==== 引数の追加

編集機能を作るために、どのデータを修正するのかという情報が必要になります。

@<code>{InputForm(this.document);}のように引数を追加することでデータによって処理を変更することが可能になります。


==== 新規作成ボタンの修正

引数の追加を行ったので、既存の画面遷移をしていた部分を修正します。

ただ引数として渡したいものがないため、nullを渡します。

@<code>{builder: (BuildContext context) => InputForm()}
　→　
@<code>{builder: (BuildContext context) => InputForm(null)}

前のコードの一部をこのように修正しました。

==== 編集ボタンの処理追加

編集ボタンを押したときに編集できるようにコードを追加します。

タッチされたデータを引数にして、表示するクラスに情報を送信します。


==== 編集データの作成

引数として提供されたデータが実際にある場合、それぞれのWidgetにデータをセットして表示させます。

それ以外の時はデータを新規作成させます。

Firestore.instance.collection('kasikari-memo').document();を使いどこにデータを保存するのか指定をします。
