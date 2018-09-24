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
//image[anonymous][匿名]{
//}

4.メール/パスワード、匿名が有効になっていれば問題ありません。
//image[complete][匿名]{
//}

以上で管理コンソール側の準備は整いました。それでは実際にコードを書いて行きましょう。

== コードの説明