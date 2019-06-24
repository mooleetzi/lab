package myFilter;

import javax.servlet.*;
import java.io.IOException;

public class encodingFilter implements Filter {
    private String encoding=null;
    private FilterConfig fc;
    @Override
    public void init(FilterConfig filterConfig) throws ServletException {
        fc=filterConfig;
        encoding=filterConfig.getInitParameter("Encoding");
    }

    @Override
    public void destroy() {
        encoding=null;
    }

    @Override
    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
        if (encoding==null)
            encoding="UTF-8";
        servletRequest.setCharacterEncoding(encoding);
        servletResponse.setCharacterEncoding(encoding);
        servletResponse.setContentType("text/html;charset=" + encoding);
        filterChain.doFilter(servletRequest,servletResponse);
    }
}
