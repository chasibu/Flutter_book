= 登録機能の実装
この章ではアプリの画面を通して、Firebaseへデータの登録を行う機能の実装をします。
その為、触るのは「_MyInputFormState」クラスの中になります。

== 登録に使用するメソッドについて
Firestore.instance.collection('コレクション名').document()というインスタンスを生成し
データの登録を行います。


==　コードの説明
今回も改変箇所が少ないので、一部だけを抜粋して記載します。

//list[main_registration1][main.dart]{
class _MyInputFormState extends State<InputForm> {
  ・・・
  @override
  Widget build(BuildContext context) {
    var _mainReference;

    _data.lendorrent = "";
    _data.user = "";
    _data.loan = "";
    _mainReference = Firestore.instance.collection('kasikari-memo').document();

    Widget titleSection;
    titleSection = Scaffold(
      appBar: AppBar(
        title: const Text('かしかりめも'),
        actions: <Widget>[
          // action button
          IconButton(
            icon: Icon(Icons.save),
            onPressed: () {
              _data.lendorrent = lendorrent;
              _data.date = date;
              if (this._formKey.currentState.validate()) {
                _formKey.currentState.save();
                _mainReference.setData(
                    { 'lendorrent': _data.lendorrent, 'name': _data.user,
                      'loan': _data.loan, 'date': _data.date});
                Navigator.pop(context);
              }
            }
          ),
        ・・・
        ],
      ),
}
//}

データ登録用の変数は事前に、””で初期化しておきます。

「_mainReference」にFirebaseへの登録用のインスタンスを代入しておきます。
また、コレクション名には前章にて作成したコレクション名を記入します。
今回は、「kasikari-memo」としております。
実際の登録処理は_mainReference.setData()内で行われております。


//list[main_registration2][main.dart]{
class _MyInputFormState extends State<InputForm> {
...

  @override
  Widget build(BuildContext context) {
    body: new SafeArea(
      child:
      new Form(
        key: this._formKey,
        child: new ListView(
          padding: const EdgeInsets.all(20.0),
          children: <Widget>[
          ・・・

          new TextFormField(
            //controller: _myController,
            decoration: const InputDecoration(
              icon: const Icon(Icons.person),
              hintText: '相手の名前',
              labelText: 'Name',
            ),
            onSaved: (String value) {
              this._data.user = value;
            },
            validator: (value) {
              if (value.isEmpty) {
                return '名前は必須入力項目です';
              }
            },
            initialValue: _data.user,
          ),

          new TextFormField(
            //controller: _myController2,
            decoration: const InputDecoration(
              icon: const Icon(Icons.business_center),
              hintText: '借りたもの、貸したもの',
              labelText: 'loan',
            ),
            onSaved: (String value) {
              this._data.loan = value;
            },
            validator: (value) {
              if (value.isEmpty) {
                return '借りたもの、貸したものは必須入力項目です';
              }
            },
            initialValue: _data.loan,
          ),
          ...

        ]
      )
    )
  )
  return titleSection;
  }
}
//}

貸し借りした人物や貸し借りした物の記載箇所に変更になります。
「TextFormField」内の「onSaved:」において、入力したデータを登録用の変数「_data」内の各変数に
代入します。

ここまでの記述が完了したら、一度アプリを立ち上げてみましょう。
新規登録画面にて登録内容記載ご、右上の保存ボタンを選択すると、一覧画面に戻り、登録した内容が表示されます。
