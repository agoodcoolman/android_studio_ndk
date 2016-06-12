package test;

import com.deao.io.android.anntion.Get;
import com.deao.io.android.anntion.GetParame;

/**
 * Created by root on 16-5-14.
 */
@Get(getUri = "/login")
public interface LoginUri {
    public void login(@GetParame(parame = "username") String username, @GetParame(parame = "password") String password);
}
