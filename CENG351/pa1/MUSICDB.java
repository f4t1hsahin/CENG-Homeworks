package ceng.ceng351.musicdb;

import java.util.List;
import java.util.ArrayList;
import ceng.ceng351.musicdb.QueryResult.ArtistNameNumberOfSongsResult;
import ceng.ceng351.musicdb.QueryResult.ArtistNameSongNameGenreRatingResult;
import ceng.ceng351.musicdb.QueryResult.UserIdUserNameNumberOfSongsResult;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;


public class MUSICDB implements IMUSICDB{
    
    private static String user = "e2171155"; // TODO: Your userName
    private static String password = "1924dd62"; //  TODO: Your password
    private static String host = "144.122.71.57"; // host name
    private static String database = "db2171155"; // TODO: Your database name
    private static int port = 8084; // port
    
    private Connection connection = null;

    /**
    * Place your initialization code inside if required.
    * 
    * <p>
    * This function will be called before all other operations. If your implementation
    * need initialization , necessary operations should be done inside this function. For
    * example, you can set your connection to the database server inside this function.
    */
   public void initialize(){
    String url = "jdbc:mysql://" + this.host + ":" + this.port + "/" + this.database;
    //String url = "jdbc:mysql://144.122.71.57:8084/db2171155"

    try {
            Class.forName("com.mysql.jdbc.Driver");
            this.connection =  DriverManager.getConnection(url, this.user, this.password);
        } 
        catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        } 


   }


   
   /**
    * Should create the necessary tables when called.
    * 
    * @return the number of tables that are created successfully.
    */
   @Override
   public int createTables(){
      int count = 0;
      String query1 = "create table user("+
        "userID int,"+
        "userName varchar(60),"+
        "email varchar(30),"+
        "password varchar(30),"+
        "primary key(userID));";
      int result;

      try {
            Statement statement = this.connection.createStatement();

            //Player Table
            result = statement.executeUpdate(query1);
            //System.out.println(result);
            count++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

      String query2 = "create table artist("+
        "artistID int,"+
        "artistName varchar(60),"+
        "primary key(artistID));";
      try {
            Statement statement = this.connection.createStatement();

            //Player Table
            result = statement.executeUpdate(query2);
            //System.out.println(result);
            count++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

      String query3 = "create table album("+
        "albumID int,"+
        "title varchar(60),"+
        "albumGenre varchar(30),"+
        "albumRating double,"+
        "releaseDate date,"+
        "artistID int,"+
        "primary key(albumID),"+
        "foreign key(artistID) references artist(artistID));";

      try {
            Statement statement = this.connection.createStatement();

            //Player Table
            result = statement.executeUpdate(query3);
            //System.out.println(result);
            count++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

      String query4 = "create table song("+
        "songID int,"+
        "songName varchar(60),"+
        "genre varchar(30),"+
        "rating double,"+
        "artistID int,"+
        "albumID int,"+
        "primary key(songID),"+
        "foreign key(artistID) references artist(artistID),"+
        "foreign key(albumID) references album(albumID));";

      try {
            Statement statement = this.connection.createStatement();

            //Player Table
            result = statement.executeUpdate(query4);
            //System.out.println(result);
            count++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
      
      
      String query5 = "create table listen("+
        "userID int,"+
        "songID int,"+
        "lastListenTime timestamp,"+
        "listenCount int,"+
        "primary key(userID, songID),"+
        "foreign key(userID) references user(userID),"+
        "foreign key(songID) references song(songID));";

        try {
            Statement statement = this.connection.createStatement();

            //Player Table
            result = statement.executeUpdate(query5);
            //System.out.println(result);
            count++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
      return count;

   }
   
   /**
    * Should drop the tables if exists when called. 
    * 
    * @return the number of tables are dropped successfully.
    */
   @Override
   public int dropTables(){
      String query1 = "Drop table user";
      String query2 = "Drop table album";
      String query3 = "Drop table artist";
      String query4 = "Drop table song";
      String query5 = "Drop table listen";
      int result;
      int count = 0;

      try {
            Statement statement = this.connection.createStatement();

            //Player Table
            result = statement.executeUpdate(query1);
            //System.out.println(result);
            count++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        try {
            Statement statement = this.connection.createStatement();

            //Player Table
            result = statement.executeUpdate(query2);
            //System.out.println(result);
            count++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        try {
            Statement statement = this.connection.createStatement();

            //Player Table
            result = statement.executeUpdate(query3);
            //System.out.println(result);
            count++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        try {
            Statement statement = this.connection.createStatement();

            //Player Table
            result = statement.executeUpdate(query4);
            //System.out.println(result);
            count++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        try {
            Statement statement = this.connection.createStatement();

            //Player Table
            result = statement.executeUpdate(query5);
            //System.out.println(result);
            count++;

            //close
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return count;
   }
   
   /**
    * Should insert an array of Album into the database.
    * 
    * @return Number of rows inserted successfully.
    */
   @Override
   public int insertAlbum(Album[] albums){
        int count = 0;
      int result;

        for(int i = 0; i < albums.length; ++i){
          Album temp_album = albums[i];
          String query = "insert into album values ('" +
                          temp_album.getAlbumID()+"','"+
                          temp_album.getTitle()+"','"+
                          temp_album.getAlbumGenre()+"','"+
                          temp_album.getAlbumRating()+"','"+
                          temp_album.getReleaseDate()+"','"+
                          temp_album.getArtistID()+"')";
          try{
            Statement st = this.connection.createStatement();
            result = st.executeUpdate(query);
            count++;
            st.close();
          } catch (SQLException e) {
            if (e.toString().contains("SQLIntegrityConstraintViolationException")){
              e.printStackTrace();
            }
          }

        }
        return count;
   }

   /**
    * Should insert an array of Artist into the database.
    * 
    * @return Number of rows inserted successfully.
    */
   @Override
   public int insertArtist(Artist[] artists){
    int count = 0;
      int result;

    for(int i = 0; i < artists.length; ++i){
      Artist temp_artist = artists[i];
      String query = "insert into artist values ('"+
                      temp_artist.getArtistID()+"','"+
                      temp_artist.getArtistName()+"')";

      try{
        Statement st = this.connection.createStatement();
        result = st.executeUpdate(query);
        count++;
        st.close();
      } catch (SQLException e) {
            if (e.toString().contains("SQLIntegrityConstraintViolationException")){
              e.printStackTrace();
            }
          }
    }
    return count;
   }

   /**
    * Should insert an array of Song into the database.
    * 
    * @return Number of rows inserted successfully.
    */
   @Override
   public int insertSong(Song[] songs){
      int count = 0;
      int result;

      for(int i = 0; i < songs.length; ++i){
        Song temp_song = songs[i];
        String query = "insert into album values ('" +
                        temp_song.getSongID()+"','"+
                        temp_song.getSongName()+"','"+
                        temp_song.getGenre()+"','"+
                        temp_song.getRating()+"','"+
                        temp_song.getArtistID()+"','"+
                        temp_song.getAlbumID()+"')";
        try{
          Statement st = this.connection.createStatement();
          result = st.executeUpdate(query);
          count++;
          st.close();
        } catch (SQLException e) {
          if (e.toString().contains("SQLIntegrityConstraintViolationException")){
            e.printStackTrace();
          }
        }

      }
      return count;

   }

   /**
    * Should insert an array of User into the database.
    * 
    * @return Number of rows inserted successfully.
    */
   @Override
   public int insertUser(User[] users){
      int count = 0;
      int result;

      for(int i = 0; i < users.length; ++i){
        User temp_user = users[i];
        String query = "insert into album values ('" +
                        temp_user.getUserID()+"','"+
                        temp_user.getUserName()+"','"+
                        temp_user.getEmail()+"','"+
                        temp_user.getPassword()+"')";
        try{
          Statement st = this.connection.createStatement();
          result = st.executeUpdate(query);
          count++;
          st.close();
        } catch (SQLException e) {
          if (e.toString().contains("SQLIntegrityConstraintViolationException")){
            e.printStackTrace();
          }
        }

      }
      return count;
   }
   
   /**
    * Should insert an array of Listen into the database.
    * 
    * @return Number of rows inserted successfully.
    */
   @Override
   public int insertListen(Listen[] listens){
      int count = 0;
      int result;

      for(int i = 0; i < listens.length; ++i){
        Listen temp_listen = listens[i];
        String query = "insert into album values ('" +
                        temp_listen.getUserID()+"','"+
                        temp_listen.getSongID()+"','"+
                        temp_listen.getLastListenTime()+"','"+
                        temp_listen.getListenCount()+"')";
        try{
          Statement st = this.connection.createStatement();
          result = st.executeUpdate(query);
          count++;
          st.close();
        } catch (SQLException e) {
          if (e.toString().contains("SQLIntegrityConstraintViolationException")){
            e.printStackTrace();
          }
        }

      }
      return count;
   }
   
   /**
    * Should return songs with the highest rating
    * 
    * @return ArtistNameSongNameGenreRatingResult[]
    */
   @Override
   public QueryResult.ArtistNameSongNameGenreRatingResult[] getHighestRatedSongs(){
      String query = "select a.artistName, s.songName, s.genre, s.rating"+
                    " from song s, artist a where a.artistId=s.artistID and s.rating = (select max(s1.rating) from song s1)"+
                    " order by a.artistName;";
      List<QueryResult.ArtistNameSongNameGenreRatingResult> lst = new ArrayList<QueryResult.ArtistNameSongNameGenreRatingResult>();
      
      try{
        Statement st = this.connection.createStatement();
        ResultSet rs = st.executeQuery(query);
        while(rs.next()){
          String a_name = rs.getString("artistName");
          String s_name = rs.getString("songName");
          String g_name = rs.getString("genre");
          double rating = rs.getDouble("rating");

          QueryResult.ArtistNameSongNameGenreRatingResult temp = new QueryResult.ArtistNameSongNameGenreRatingResult(a_name, s_name, g_name, rating);
          lst.add(temp);
        }
        st.close();


      } catch (SQLException e) {
            e.printStackTrace();
        }
      int sz = lst.size();
      QueryResult.ArtistNameSongNameGenreRatingResult[] res = new QueryResult.ArtistNameSongNameGenreRatingResult[sz];
      lst.toArray(res);
      return res;
   }
   
   /**
    * Should return the most recent album for the given artistName
    * 
    * @return TitleReleaseDateRatingResult
    */
   @Override
   public QueryResult.TitleReleaseDateRatingResult getMostRecentAlbum(String artistName){
      String query = "select alb.title, alb.releaseDate, alb.albumRating"+
                    " from album alb, artist art where art.artistName='" +artistName+"' and art.artistID=alb.artistID and"+
                    " alb.releaseDate = (select max(alb1.releaseDate) from album alb1);";

      QueryResult.TitleReleaseDateRatingResult res = null;
      try{
        Statement st = this.connection.createStatement();
        ResultSet rs = st.executeQuery(query);
        rs.next();
        String title = rs.getString("title");
        String releaseDate = rs.getString("releaseDate");
        double rating = rs.getDouble("albumRating");
        res = new QueryResult.TitleReleaseDateRatingResult(title, releaseDate, rating);
        st.close();

      } catch(SQLException e){
          e.printStackTrace();
      }
      return res;

   }



   /** 
    * Should return songs that are listened by both users whose usernames are given
    * 
    * @return ArtistNameSongNameGenreRatingResult[]
    */
   @Override
   public QueryResult.ArtistNameSongNameGenreRatingResult[] getCommonSongs(String userName1, String userName2){
      String query = "select art.artistName, s.songName, s.genre, s.rating from"+
                  " artist art, song s where s.songID in (select l1.songID from"+
                  " listen l1, listen l2, user u1, user u2 where u1.userName='"+userName1 +"' and u2.userName='"+userName2+
                  "' and l1.userID=u1.userID and l2.userID=u2.userID)"+
                  " order by s.rating desc;";
      List<QueryResult.ArtistNameSongNameGenreRatingResult> lst = new ArrayList<QueryResult.ArtistNameSongNameGenreRatingResult>();
      
      try{
        Statement st = this.connection.createStatement();
        ResultSet rs = st.executeQuery(query);
        while(rs.next()){
          String a_name = rs.getString("artistName");
          String s_name = rs.getString("songName");
          String g_name = rs.getString("genre");
          double rating = rs.getDouble("rating");

          QueryResult.ArtistNameSongNameGenreRatingResult temp = new QueryResult.ArtistNameSongNameGenreRatingResult(a_name, s_name, g_name, rating);
          lst.add(temp);
        }
        st.close();


      } catch (SQLException e) {
            e.printStackTrace();
        }
      int sz = lst.size();
      QueryResult.ArtistNameSongNameGenreRatingResult[] res = new QueryResult.ArtistNameSongNameGenreRatingResult[sz];
      lst.toArray(res);
      return res;


   }
   
   /**
    * Should return artists whose songs are listened by the given user 
    * and number of times his/her songs have been listened by the given user
    * 
    * @return ArtistNameNumberOfSongsResult[]
    */
   @Override
   public QueryResult.ArtistNameNumberOfSongsResult[] getNumberOfTimesSongsListenedByUser(String userName){
      String query = "select art.artistName, list.listenCount from"+ 
                    " artist art, listen list, user usr, song s where"+
                    " usr.userName='"+userName+"' and usr.usrID=list.userID and list.songID=s.songID and s.artistID=art.artistID"+
                    " order by art.artistName;";
      List<QueryResult.ArtistNameNumberOfSongsResult> lst = new ArrayList<QueryResult.ArtistNameNumberOfSongsResult>();


      try{
        Statement st = this.connection.createStatement();
        ResultSet rs = st.executeQuery(query);
        while(rs.next()){
          String a_name = rs.getString("artistName");
          int num = rs.getInt("listenCount");
          QueryResult.ArtistNameNumberOfSongsResult temp = new QueryResult.ArtistNameNumberOfSongsResult(a_name, num);
          lst.add(temp);
        } 
        st.close();

      } catch (SQLException e) {
            e.printStackTrace();
        }

      int sz = lst.size();
      QueryResult.ArtistNameNumberOfSongsResult[] res = new QueryResult.ArtistNameNumberOfSongsResult[sz];
      lst.toArray(res);
      return res;
   }
   
   /**
    * Should return users who have listened all songs of a given artist
    * 
    * @return User[]
    */
   @Override
   public User[] getUsersWhoListenedAllSongs(String artistName){
      String query = "select u.userID from user u where not exists"+ 
                    " (select * from song s where not exists "+
                    " (select l.songID from listen l where l.songID=s.songID and l.userID=u.userID))"+
                    " order by u.userID;";
      List<User> lst = new ArrayList<User>();
      try{
        Statement st=this.connection.createStatement();
        ResultSet rs = st.executeQuery(query);
        while(rs.next()){
          int id = rs.getInt("userID");
          String u_name = rs.getString("userName");
          String e_name = rs.getString("email");
          String p_name = rs.getString("password");
          User temp = new User(id, u_name, e_name, p_name);
          lst.add(temp);
        }
        st.close();

      } catch (SQLException e){
        e.printStackTrace();
      }
      int sz = lst.size();
      User[] res = new User[sz];
      lst.toArray(res);
      return res;
   }
   
   /**
    * Should return the userID, userName and number of songs listened by this user such that 
    * none of these songs are listened by any other user.
    * 
    * @return QueryResult.UserIdUserNameNumberOfSongsResult[]
    */
   public QueryResult.UserIdUserNameNumberOfSongsResult[]  getUserIDUserNameNumberOfSongsNotListenedByAnyone(){
    return null;
   }
   
   /**
    * Should return artists who have sung pop music at least once and whose average rating of
    * all songs is greater than the given rating
    * 
    * @return Artist[]
    */
   @Override
   public Artist[] getArtistSingingPopGreaterAverageRating(double rating){
      String query = "select a.artistID, a.artistName from artist a where a.artistID in "+
                    "(select s.artistID fromsong s where"+
                    " s.genre='Pop'"+
                    " intersect "+
                    " select s.artistID from song s where"+
                    "group by s.artist ID "+
                    "having avg(s.rating) >"+rating+")"+
                    "order by a.artistID;";
      List<Artist> lst = new ArrayList<Artist>();
      try{
        Statement st=this.connection.createStatement();
        ResultSet rs = st.executeQuery(query);
        while(rs.next()){
          int id = rs.getInt("artistID");
          String a_name = rs.getString("artistName");
          Artist temp = new Artist(id,a_name);
          lst.add(temp);
        }
        st.close();

      } catch (SQLException e){
        e.printStackTrace();
      }

      int sz = lst.size();
      Artist[] res = new Artist[sz];
      lst.toArray(res);
      return res;
   }
   
   /**
    * Retrieve songs with the lowest rating in pop category, in case of more than one song exist, 
    * retrieve the least listened ones
    * 
    * @return Song[]
    */
   @Override
   public Song[] retrieveLowestRatedAndLeastNumberOfListenedSongs(){
      String query = "select s.songID, s.songName, s.rating, s.genre, s.artistID, s.albumID"+
                    " from song s where s.genre='Pop' and s.rating = (select min(s1.rating) from song s1)";
      return null;
   }
   
   /**
    * Multiply the rating of the album by 1.5 whose releaseDate is after for a given date
    * 
    * @return the row count for SQL Data Manipulation Language (DML) statements
    */
   public int multiplyRatingOfAlbum(String releaseDate){
      String query = "update album set albumRating=albumRating*1.5 where releaseDate > " + releaseDate + ";";
      int result = 0;
      try{
        Statement st = this.connection.createStatement();
        result = st.executeUpdate(query);
        st.close();
      } catch(SQLException e) {
        e.printStackTrace();
      }

      return result;
   }
   
   /**
    * Delete the song for the given songName
    * 
    * @return Song
    */
   @Override
   public Song deleteSong(String songName){
    String query_delete = "delete from song where songName='" + songName+"';";
    String query_select = "select s.songID, s.songName, s.genre, s.rating, s.artistID, s.albumID"+
                        "  from song s where s.songName='" + songName+"';";
    Song res = null;
      int result = 0;

    try{
        Statement st = this.connection.createStatement();
        ResultSet rs = st.executeQuery(query_select);
        rs.next();
        int id = rs.getInt("songID");
        String s_name = rs.getString("songName");
        String genre = rs.getString("genre");
        double rating = rs.getDouble("rating");
        int art_id = rs.getInt("artistID");
        int alb_id = rs.getInt("albumID");
        res = new Song(id, s_name, genre, rating, art_id, alb_id);
        st.close();
    } catch(SQLException e){
      e.printStackTrace();
    }
    try{
        Statement st = this.connection.createStatement();

        result = st.executeUpdate(query_delete);
        st.close();
      } catch(SQLException e) {
        e.printStackTrace();
      }

      return res;
   }
   
}
