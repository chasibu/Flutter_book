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

編集ボタンを選択後、@<code>{MaterialPageRoute}を利用し画面遷移を実現します。
ドキュメントIDを引数として、@<code>{InputForm(document)}を実行することで、
入力画面に対象のドキュメントIDを引き渡します。


== 登録データの呼び出しについて
登録データを呼び出すには@<code>{Firestore.instance.collection(”コレクション名”).document(”ドキュメントID”)}
を使用します。

全体的な動きは次のとおりになります。

1. 一覧画面から編集したいデータを選択。その際に、対象のデータのドキュメントIDを表示画面先に渡す。

2. 受け取ったドキュメントIDを元にFirestoreからデータを取得。

3. 紐づいているキーの値を元に入力フォームに値を入力。

4. 保存ボタンを押して、データの登録を行う。

今回は、一覧画面側@<code>{_buildListItem()}と編集画面側@<code>{_MyInputFormState()}でコードの編集を行います。
まずは、一覧画面から編集画面に対してドキュメントIDを渡す箇所についてです。

@<code>{InputForm(this.document);}と追加することで、@<code>{InputForm}に対して、
引数をひとつ追加します。こうすることで、編集ボタンを押した際にドキュメントIDを
遷移先に引き渡すことができます。


== 入力フォームへ値の代入

@<code>{_MyInputFormState}を呼び出し直後、@<code>{widget.document}の有無を判定します。
データがある場合には、データ格納用の変数@<code>{_data}にFirestoreに登録されているデータを代入します。
また、@<code>{_mainReference}に呼び出したIDに対応する、Firestoreのインスタンスを生成します。
無い場合には、IDを指定しないでFirestoreのインスタンスを生成(新規作成)します。

== 新規作成ボタンの変更

新規作成ボタンを選択後に、@<code>{MaterialPageRoute}を使用して@<code>{InputForm(null)}を呼び出します。
@<code>{InputForm()}に引数をひとつ持たせた為、何かしら値を引き渡す必要があります。新規作成時は特別引き渡す変数が無いため
@<code>{null}を引き渡しています。

ここまで実装すると、編集機能を有効になります。
次の画像のように、実際に登録してあるデータを選択し、編集画面を開いてみましょう。
//image[list][一覧画面][scale=0.6]{
//}
//image[update][編集画面][scale=0.6]{
//}
