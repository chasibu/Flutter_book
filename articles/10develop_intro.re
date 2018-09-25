= アプリケーションの作成

== アプリケーションの仕様

本書では、何かを借りたときや貸したときに役立つ「貸し借りを記録できるメモ帳」を作成します。

次の情報をメモできるものを作成します。

 * 貸したのか借りたのか
 * 誰に
 * 何を
 * 返却期限

完成版の画面は次のとおりです。

//image[app][完成イメージ][scale=0.8]{
//}

その貸し借りの記録を他の端末から確認できるようにログイン機能とデータをクラウドに保存するためにFirebaseを使います。

今回のアプリ必要な機能は次のとおりです。

 * 一覧表示機能
 * 新規登録機能
 * 編集機能
 * 削除機能
 * ログイン機能

 これを叶えられるアプリをFlutterで作成しながら学んでいきます。

== プロジェクトの作成

プロジェクトの作成を行います。

先ほどの@<chap>{03sampleProgram}を参考にプロジェクトを作成します。

本書では「kasikari_memo」という名前をプロジェクト名にして開発を進めます。
