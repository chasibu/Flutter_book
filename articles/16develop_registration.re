= 登録機能の実装をしよう
この章ではアプリの画面を通して、Firebaseへデータの登録を行う機能の実装をします。

この章を完了すると次のタグの内容になります。
@<href>{https://github.com/chasibu/kasikari_memo/releases/tag/chapter10}

== 登録に使用するメソッドについて
Firestore.instance.collection('コレクション名').document()というインスタンスを生成し
データの登録を行います。


== データ保存
//list[main_registration1][main.dart]{
class _MyInputFormState extends State<InputForm> {

  @override
  Widget build(BuildContext context) {
  DocumentReference _mainReference;
  _mainReference = Firestore.instance.collection('kasikari-memo').document();

  return Scaffold(
  appBar: AppBar(
    title: const Text('かしかり入力'),
    actions: <Widget>[
      IconButton(
          icon: Icon(Icons.save),
          onPressed: () {
            print("保存ボタンを押しました");
            if (_formKey.currentState.validate()) {
              _formKey.currentState.save();
              _mainReference.setData(
                  {
                    'borrowOrLend': _data.borrowOrLend,
                    'user': _data.user,
                    'stuff': _data.stuff,
                    'date': _data.date
                  });
              Navigator.pop(context);
            }
          }
      ),
      IconButton(
        ...
      )
    ],
  ),
  ...
  )
  }
}
//}

Firestoreにデータを登録するために、@<code>{Firestore.instance.collection('コレクション名').document();}
を使用し、インスタンスを生成します。

保存ボタンを選択後、@<code>{_formKey}を使用し、入力チェックを行います。
入力チェクを行い、問題なければ、@<code>{_mainReference.setData()}を使用し、Firestoreへデータの登録を行います。

「"キー":"値"」の形式で、Firestoreへデータの登録を行い、４つのデータを保存したら、@<code>{Navigator.pop}を利用し
元の一覧画面に戻ります。

この状態で、アプリを実行すると、一覧画面が表示され、右下の新規作成ボタンを押すことで、新規作成画面に遷移し、新規登録が可能になります。
